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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ntpcal_periodic_extend (scalar_t__,scalar_t__,int) ; 

int32_t
ntpcal_weekday_gt(
	int32_t rdn,
	int32_t dow
	)
{
	return ntpcal_periodic_extend(rdn+1, dow, 7);
}