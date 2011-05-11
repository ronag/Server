/*
* copyright (c) 2010 Sveriges Television AB <info@casparcg.com>
*
*  This file is part of CasparCG.
*
*    CasparCG is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    CasparCG is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with CasparCG.  If not, see <http://www.gnu.org/licenses/>.
*
*/
#pragma once

#include "frame_visitor.h"
#include "../../video_format.h"

#include <common/memory/safe_ptr.h>

#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>

#include <array>
#include <memory>
#include <vector>

namespace caspar { namespace core {

class image_transform;
class audio_transform;
		
class basic_frame
{
public:
	basic_frame();	
	basic_frame(const safe_ptr<basic_frame>& frame);
	basic_frame(safe_ptr<basic_frame>&& frame);
	basic_frame(const std::vector<safe_ptr<basic_frame>>& frames);
	basic_frame(std::vector<safe_ptr<basic_frame>>&& frame);
	basic_frame(const safe_ptr<basic_frame>& frame1, const safe_ptr<basic_frame>& frame2);
	basic_frame(safe_ptr<basic_frame>&& frame1, safe_ptr<basic_frame>&& frame2);

	void swap(basic_frame& other);
	
	basic_frame(const basic_frame& other);
	basic_frame(basic_frame&& other);

	basic_frame& operator=(const basic_frame& other);
	basic_frame& operator=(basic_frame&& other);
	
	const image_transform& get_image_transform() const;
	image_transform& get_image_transform();

	const audio_transform& get_audio_transform() const;
	audio_transform& get_audio_transform();
		
	static safe_ptr<basic_frame> interlace(const safe_ptr<basic_frame>& frame1, const safe_ptr<basic_frame>& frame2, video_mode::type mode);
		
	static const safe_ptr<basic_frame>& eof()
	{
		static safe_ptr<basic_frame> frame = make_safe<basic_frame>();
		return frame;
	}

	static const safe_ptr<basic_frame>& empty()
	{
		static safe_ptr<basic_frame> frame = make_safe<basic_frame>();
		return frame;
	}
	
	virtual void accept(frame_visitor& visitor);
private:
	struct implementation;
	std::shared_ptr<implementation> impl_;
};

}}