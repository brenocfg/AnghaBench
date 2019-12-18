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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ doorbell_irqs; scalar_t__ soft_nmi_irqs; scalar_t__ sreset_irqs; scalar_t__ hmi_exceptions; scalar_t__ timer_irqs_others; scalar_t__ spurious_irqs; scalar_t__ mce_exceptions; scalar_t__ pmu_irqs; scalar_t__ broadcast_irqs_event; int /*<<< orphan*/  timer_irqs_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_stat ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

u64 arch_irq_stat_cpu(unsigned int cpu)
{
	u64 sum = per_cpu(irq_stat, cpu).timer_irqs_event;

	sum += per_cpu(irq_stat, cpu).broadcast_irqs_event;
	sum += per_cpu(irq_stat, cpu).pmu_irqs;
	sum += per_cpu(irq_stat, cpu).mce_exceptions;
	sum += per_cpu(irq_stat, cpu).spurious_irqs;
	sum += per_cpu(irq_stat, cpu).timer_irqs_others;
	sum += per_cpu(irq_stat, cpu).hmi_exceptions;
	sum += per_cpu(irq_stat, cpu).sreset_irqs;
#ifdef CONFIG_PPC_WATCHDOG
	sum += per_cpu(irq_stat, cpu).soft_nmi_irqs;
#endif
#ifdef CONFIG_PPC_DOORBELL
	sum += per_cpu(irq_stat, cpu).doorbell_irqs;
#endif

	return sum;
}