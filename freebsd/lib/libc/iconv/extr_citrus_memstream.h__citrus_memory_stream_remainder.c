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

/* Variables and functions */
 size_t _citrus_region_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline size_t
_citrus_memory_stream_remainder(struct _citrus_memory_stream *ms)
{
	size_t sz;

	sz = _citrus_region_size(&ms->ms_region);
	if (ms->ms_pos>sz)
		return (0);
	return (sz-ms->ms_pos);
}