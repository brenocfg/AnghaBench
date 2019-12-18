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
 int /*<<< orphan*/  CPUHP_AP_MIPS_GIC_TIMER_STARTING ; 
 int ENXIO ; 
 int /*<<< orphan*/  cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_compare_irqaction ; 
 int /*<<< orphan*/  gic_dying_cpu ; 
 int /*<<< orphan*/  gic_frequency ; 
 int /*<<< orphan*/  gic_starting_cpu ; 
 int /*<<< orphan*/  gic_timer_irq ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int setup_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gic_clockevent_init(void)
{
	int ret;

	if (!gic_frequency)
		return -ENXIO;

	ret = setup_percpu_irq(gic_timer_irq, &gic_compare_irqaction);
	if (ret < 0) {
		pr_err("IRQ %d setup failed (%d)\n", gic_timer_irq, ret);
		return ret;
	}

	cpuhp_setup_state(CPUHP_AP_MIPS_GIC_TIMER_STARTING,
			  "clockevents/mips/gic/timer:starting",
			  gic_starting_cpu, gic_dying_cpu);
	return 0;
}