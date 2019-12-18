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
struct irq_data {int dummy; } ;
struct TYPE_2__ {unsigned long txn_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_data ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  irq_data_get_affinity_mask (struct irq_data*) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 

unsigned long txn_affinity_addr(unsigned int irq, int cpu)
{
#ifdef CONFIG_SMP
	struct irq_data *d = irq_get_irq_data(irq);
	cpumask_copy(irq_data_get_affinity_mask(d), cpumask_of(cpu));
#endif

	return per_cpu(cpu_data, cpu).txn_addr;
}