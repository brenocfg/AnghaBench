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
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int cpu_online (int) ; 
 int cpumask_test_cpu (int,struct cpumask const*) ; 
 struct cpumask const* irq_data_get_affinity_mask (struct irq_data*) ; 
 scalar_t__ irqd_affinity_was_set (struct irq_data*) ; 

__attribute__((used)) static inline int enable_irq_for_cpu(int cpu, struct irq_data *d,
				     const struct cpumask *m)
{
	bool enable = cpu_online(cpu);

#ifdef CONFIG_SMP
	if (m)
		enable &= cpumask_test_cpu(cpu, m);
	else if (irqd_affinity_was_set(d))
		enable &= cpumask_test_cpu(cpu, irq_data_get_affinity_mask(d));
#endif
	return enable;
}