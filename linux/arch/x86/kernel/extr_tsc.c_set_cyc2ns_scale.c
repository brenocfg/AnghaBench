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
 int /*<<< orphan*/  __set_cyc2ns_scale (unsigned long,int,unsigned long long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sched_clock_idle_sleep_event () ; 
 int /*<<< orphan*/  sched_clock_idle_wakeup_event () ; 

__attribute__((used)) static void set_cyc2ns_scale(unsigned long khz, int cpu, unsigned long long tsc_now)
{
	unsigned long flags;

	local_irq_save(flags);
	sched_clock_idle_sleep_event();

	if (khz)
		__set_cyc2ns_scale(khz, cpu, tsc_now);

	sched_clock_idle_wakeup_event();
	local_irq_restore(flags);
}