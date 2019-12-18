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
struct _citrus_region {int dummy; } ;
struct _citrus_memory_stream {scalar_t__ ms_pos; int /*<<< orphan*/  ms_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  _citrus_region_init (struct _citrus_region*,void*,size_t) ; 
 void* _citrus_region_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ _citrus_region_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void *
_citrus_memory_stream_getregion(struct _citrus_memory_stream *ms,
    struct _citrus_region *r, size_t sz)
{
	void *ret;

	if (ms->ms_pos + sz > _citrus_region_size(&ms->ms_region))
		return (NULL);

	ret = _citrus_region_offset(&ms->ms_region, ms->ms_pos);
	ms->ms_pos += sz;
	if (r)
		_citrus_region_init(r, ret, sz);

	return (ret);
}