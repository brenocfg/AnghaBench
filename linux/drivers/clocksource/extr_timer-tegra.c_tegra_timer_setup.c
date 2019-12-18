#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct timer_of {TYPE_1__ clkevt; } ;

/* Variables and functions */
 scalar_t__ TIMER_PCR ; 
 int /*<<< orphan*/  TIMER_PCR_INTR_CLR ; 
 scalar_t__ TIMER_PTV ; 
 int /*<<< orphan*/  clockevents_config_and_register (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_force_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timer_of* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tegra_to ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  timer_of_rate (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_timer_setup(unsigned int cpu)
{
	struct timer_of *to = per_cpu_ptr(&tegra_to, cpu);

	writel_relaxed(0, timer_of_base(to) + TIMER_PTV);
	writel_relaxed(TIMER_PCR_INTR_CLR, timer_of_base(to) + TIMER_PCR);

	irq_force_affinity(to->clkevt.irq, cpumask_of(cpu));
	enable_irq(to->clkevt.irq);

	/*
	 * Tegra's timer uses n+1 scheme for the counter, i.e. timer will
	 * fire after one tick if 0 is loaded and thus minimum number of
	 * ticks is 1. In result both of the clocksource's tick limits are
	 * higher than a minimum and maximum that hardware register can
	 * take by 1, this is then taken into account by set_next_event
	 * callback.
	 */
	clockevents_config_and_register(&to->clkevt, timer_of_rate(to),
					1, /* min */
					0x1fffffff + 1); /* max 29 bits + 1 */

	return 0;
}