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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_time_cal {int /*<<< orphan*/  fcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_tcal_have_fcr (struct pt_time_cal const*) ; 
 int pte_internal ; 
 int pte_no_time ; 

int pt_tcal_fcr(uint64_t *fcr, const struct pt_time_cal *tcal)
{
	if (!fcr || !tcal)
		return -pte_internal;

	if (!pt_tcal_have_fcr(tcal))
		return -pte_no_time;

	*fcr = tcal->fcr;

	return 0;
}