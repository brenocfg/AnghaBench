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
 int /*<<< orphan*/  drift_comp ; 
 int kern_enable ; 
 scalar_t__ loop_started ; 
 scalar_t__ pll_control ; 
 int /*<<< orphan*/  set_freq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_kern_loop () ; 
 int /*<<< orphan*/  stop_kern_loop () ; 

void
select_loop(
	int	use_kern_loop
	)
{
	if (kern_enable == use_kern_loop)
		return;
#ifdef KERNEL_PLL
	if (pll_control && !use_kern_loop)
		stop_kern_loop();
#endif
	kern_enable = use_kern_loop;
#ifdef KERNEL_PLL
	if (pll_control && use_kern_loop)
		start_kern_loop();
#endif
	/*
	 * If this loop selection change occurs after initial startup,
	 * call set_freq() to switch the frequency compensation to or
	 * from the kernel loop.
	 */
#ifdef KERNEL_PLL
	if (pll_control && loop_started)
		set_freq(drift_comp);
#endif
}