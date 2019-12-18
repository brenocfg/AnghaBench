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
struct TYPE_2__ {int /*<<< orphan*/  cpumask; } ;
struct timer_of {TYPE_1__ clkevt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  clockevents_config_and_register (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  csky_mptimer_irq ; 
 int /*<<< orphan*/  csky_to ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timer_of* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  timer_of_rate (struct timer_of*) ; 

__attribute__((used)) static int csky_mptimer_starting_cpu(unsigned int cpu)
{
	struct timer_of *to = per_cpu_ptr(&csky_to, cpu);

	to->clkevt.cpumask = cpumask_of(cpu);

	enable_percpu_irq(csky_mptimer_irq, 0);

	clockevents_config_and_register(&to->clkevt, timer_of_rate(to),
					2, ULONG_MAX);

	return 0;
}