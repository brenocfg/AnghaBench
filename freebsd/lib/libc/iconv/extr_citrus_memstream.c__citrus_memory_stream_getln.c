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
typedef  int /*<<< orphan*/  uint8_t ;
struct _citrus_memory_stream {scalar_t__ ms_pos; int /*<<< orphan*/  ms_region; } ;

/* Variables and functions */
 scalar_t__ _bcs_iseol (int /*<<< orphan*/  const) ; 
 scalar_t__ _region_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ _region_size (int /*<<< orphan*/ *) ; 

const char *
_citrus_memory_stream_getln(struct _citrus_memory_stream * __restrict ms,
    size_t * __restrict rlen)
{
	const uint8_t *h, *p;
	size_t i, ret;

	if (ms->ms_pos>=_region_size(&ms->ms_region))
		return (NULL);

	h = p = (uint8_t *)_region_offset(&ms->ms_region, ms->ms_pos);
	ret = 0;
	for (i = _region_size(&ms->ms_region) - ms->ms_pos; i > 0; i--) {
		ret++;
		if (_bcs_iseol(*p))
			break;
		p++;
	}

	ms->ms_pos += ret;
	*rlen = ret;
	return ((const char *)h);
}