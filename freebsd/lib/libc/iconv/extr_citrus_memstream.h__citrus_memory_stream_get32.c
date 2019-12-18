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
typedef  int /*<<< orphan*/  uint32_t ;
struct _citrus_memory_stream {scalar_t__ ms_pos; int /*<<< orphan*/  ms_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  _citrus_region_peek32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ _citrus_region_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
_citrus_memory_stream_get32(struct _citrus_memory_stream *ms, uint32_t *rval)
{

	if (ms->ms_pos + 4 > _citrus_region_size(&ms->ms_region))
		return (-1);

	*rval = _citrus_region_peek32(&ms->ms_region, ms->ms_pos);
	ms->ms_pos += 4;

	return (0);
}