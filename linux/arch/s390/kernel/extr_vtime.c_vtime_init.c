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

/* Variables and functions */
 int /*<<< orphan*/  MT_DIAG ; 
 int /*<<< orphan*/  VTIMER_MAX_SLICE ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int jiffies ; 
 int /*<<< orphan*/  mt_cycles ; 
 int /*<<< orphan*/  mt_scaling_div ; 
 int /*<<< orphan*/  mt_scaling_jiffies ; 
 int /*<<< orphan*/  mt_scaling_mult ; 
 int /*<<< orphan*/  set_vtimer (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_cpu_mtid ; 
 int /*<<< orphan*/  stcctm (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

void vtime_init(void)
{
	/* set initial cpu timer */
	set_vtimer(VTIMER_MAX_SLICE);
	/* Setup initial MT scaling values */
	if (smp_cpu_mtid) {
		__this_cpu_write(mt_scaling_jiffies, jiffies);
		__this_cpu_write(mt_scaling_mult, 1);
		__this_cpu_write(mt_scaling_div, 1);
		stcctm(MT_DIAG, smp_cpu_mtid + 1, this_cpu_ptr(mt_cycles));
	}
}