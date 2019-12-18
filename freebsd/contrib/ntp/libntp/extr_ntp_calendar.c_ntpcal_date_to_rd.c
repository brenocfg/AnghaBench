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
struct calendar {scalar_t__ monthday; scalar_t__ month; scalar_t__ year; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ntpcal_edate_to_eradays (scalar_t__,scalar_t__,scalar_t__) ; 

int32_t
ntpcal_date_to_rd(
	const struct calendar *jd
	)
{
	return ntpcal_edate_to_eradays((int32_t)jd->year - 1,
				       (int32_t)jd->month - 1,
				       (int32_t)jd->monthday - 1) + 1;
}