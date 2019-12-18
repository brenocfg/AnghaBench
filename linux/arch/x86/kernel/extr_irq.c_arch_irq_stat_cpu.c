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
struct TYPE_2__ {scalar_t__ irq_threshold_count; scalar_t__ irq_thermal_count; scalar_t__ irq_call_count; scalar_t__ irq_resched_count; scalar_t__ x86_platform_ipis; scalar_t__ icr_read_retry_count; scalar_t__ apic_irq_work_irqs; scalar_t__ apic_perf_irqs; scalar_t__ irq_spurious_count; scalar_t__ apic_timer_irqs; int /*<<< orphan*/  __nmi_count; } ;

/* Variables and functions */
 TYPE_1__* irq_stats (unsigned int) ; 
 int /*<<< orphan*/  mce_exception_count ; 
 int /*<<< orphan*/  mce_poll_count ; 
 scalar_t__ per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ x86_platform_ipi_callback ; 

u64 arch_irq_stat_cpu(unsigned int cpu)
{
	u64 sum = irq_stats(cpu)->__nmi_count;

#ifdef CONFIG_X86_LOCAL_APIC
	sum += irq_stats(cpu)->apic_timer_irqs;
	sum += irq_stats(cpu)->irq_spurious_count;
	sum += irq_stats(cpu)->apic_perf_irqs;
	sum += irq_stats(cpu)->apic_irq_work_irqs;
	sum += irq_stats(cpu)->icr_read_retry_count;
	if (x86_platform_ipi_callback)
		sum += irq_stats(cpu)->x86_platform_ipis;
#endif
#ifdef CONFIG_SMP
	sum += irq_stats(cpu)->irq_resched_count;
	sum += irq_stats(cpu)->irq_call_count;
#endif
#ifdef CONFIG_X86_THERMAL_VECTOR
	sum += irq_stats(cpu)->irq_thermal_count;
#endif
#ifdef CONFIG_X86_MCE_THRESHOLD
	sum += irq_stats(cpu)->irq_threshold_count;
#endif
#ifdef CONFIG_X86_MCE
	sum += per_cpu(mce_exception_count, cpu);
	sum += per_cpu(mce_poll_count, cpu);
#endif
	return sum;
}