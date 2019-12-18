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
 int PWR_EVENT_EXIT ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  trace_cpu_idle_rcuidle (int,int /*<<< orphan*/ ) ; 

void arch_cpu_idle(void)
{
	/*
	 * This should do all the clock switching and wait for interrupt
	 * tricks
	 */
	trace_cpu_idle_rcuidle(1, smp_processor_id());
	cpu_do_idle();
	local_irq_enable();
	trace_cpu_idle_rcuidle(PWR_EVENT_EXIT, smp_processor_id());
}