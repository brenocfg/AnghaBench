#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ts_start; scalar_t__ ts_end; } ;
typedef  TYPE_1__ trim_seg_t ;

/* Variables and functions */

__attribute__((used)) static int
trim_map_seg_compare(const void *x1, const void *x2)
{
	const trim_seg_t *s1 = x1;
	const trim_seg_t *s2 = x2;

	if (s1->ts_start < s2->ts_start) {
		if (s1->ts_end > s2->ts_start)
			return (0);
		return (-1);
	}
	if (s1->ts_start > s2->ts_start) {
		if (s1->ts_start < s2->ts_end)
			return (0);
		return (1);
	}
	return (0);
}