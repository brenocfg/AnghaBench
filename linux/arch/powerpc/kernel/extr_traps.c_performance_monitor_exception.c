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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 TYPE_1__ irq_stat ; 
 int /*<<< orphan*/  perf_irq (struct pt_regs*) ; 

void performance_monitor_exception(struct pt_regs *regs)
{
	__this_cpu_inc(irq_stat.pmu_irqs);

	perf_irq(regs);
}