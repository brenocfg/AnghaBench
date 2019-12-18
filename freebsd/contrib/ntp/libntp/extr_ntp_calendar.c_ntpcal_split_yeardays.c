#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int hi; int lo; } ;
typedef  TYPE_1__ ntpcal_split ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__** real_month_table ; 

ntpcal_split
ntpcal_split_yeardays(
	int32_t eyd,
	int     isleapyear
	)
{
	ntpcal_split    res;
	const uint16_t *lt;	/* month length table	*/

	/* check leap year flag and select proper table */
	lt = real_month_table[(isleapyear != 0)];
	if (0 <= eyd && eyd < lt[12]) {
		/* get zero-based month by approximation & correction step */
		res.hi = eyd >> 5;	   /* approx month; might be 1 too low */
		if (lt[res.hi + 1] <= eyd) /* fixup approximative month value  */
			res.hi += 1;
		res.lo = eyd - lt[res.hi];
	} else {
		res.lo = res.hi = -1;
	}

	return res;
}