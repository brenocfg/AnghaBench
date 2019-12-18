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
typedef  scalar_t__ uint64_t ;
struct pt_time_cal {scalar_t__ min_fcr; scalar_t__ max_fcr; scalar_t__ fcr; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_tcal_set_fcr(struct pt_time_cal *tcal, uint64_t fcr)
{
	if (!tcal)
		return -pte_internal;

	tcal->fcr = fcr;

	if (fcr < tcal->min_fcr)
		tcal->min_fcr = fcr;

	if (fcr > tcal->max_fcr)
		tcal->max_fcr = fcr;

	return 0;
}