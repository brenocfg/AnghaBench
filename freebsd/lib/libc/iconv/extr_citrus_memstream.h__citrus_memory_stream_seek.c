#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _citrus_memory_stream {size_t ms_pos; int /*<<< orphan*/  ms_region; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 size_t _citrus_region_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
_citrus_memory_stream_seek(struct _citrus_memory_stream *ms, size_t pos, int w)
{
	size_t sz;

	sz = _citrus_region_size(&ms->ms_region);

	switch (w) {
	case SEEK_SET:
		if (pos >= sz)
			return (-1);
		ms->ms_pos = pos;
		break;
	case SEEK_CUR:
		pos += (ssize_t)ms->ms_pos;
		if (pos >= sz)
			return (-1);
		ms->ms_pos = pos;
		break;
	case SEEK_END:
		if (sz < pos)
			return (-1);
		ms->ms_pos = sz - pos;
		break;
	}
	return (0);
}