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
struct clock_event_device {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_TIMERN_MAX ; 
 int /*<<< orphan*/  arc_clockevent_device ; 
 int /*<<< orphan*/  arc_timer_freq ; 
 int /*<<< orphan*/  arc_timer_irq ; 
 int /*<<< orphan*/  clockevents_config_and_register (struct clock_event_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct clock_event_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arc_timer_starting_cpu(unsigned int cpu)
{
	struct clock_event_device *evt = this_cpu_ptr(&arc_clockevent_device);

	evt->cpumask = cpumask_of(smp_processor_id());

	clockevents_config_and_register(evt, arc_timer_freq, 0, ARC_TIMERN_MAX);
	enable_percpu_irq(arc_timer_irq, 0);
	return 0;
}