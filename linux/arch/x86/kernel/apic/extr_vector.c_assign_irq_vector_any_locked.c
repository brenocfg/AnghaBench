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
 int NUMA_NO_NODE ; 
 int assign_vector_locked (struct irq_data*,struct cpumask const*) ; 
 struct cpumask const* cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask const*,struct cpumask const*,struct cpumask const*) ; 
 struct cpumask const* cpumask_of_node (int) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int irq_data_get_node (struct irq_data*) ; 
 struct cpumask const* vector_searchmask ; 

__attribute__((used)) static int assign_irq_vector_any_locked(struct irq_data *irqd)
{
	/* Get the affinity mask - either irq_default_affinity or (user) set */
	const struct cpumask *affmsk = irq_data_get_affinity_mask(irqd);
	int node = irq_data_get_node(irqd);

	if (node == NUMA_NO_NODE)
		goto all;
	/* Try the intersection of @affmsk and node mask */
	cpumask_and(vector_searchmask, cpumask_of_node(node), affmsk);
	if (!assign_vector_locked(irqd, vector_searchmask))
		return 0;
	/* Try the node mask */
	if (!assign_vector_locked(irqd, cpumask_of_node(node)))
		return 0;
all:
	/* Try the full affinity mask */
	cpumask_and(vector_searchmask, affmsk, cpu_online_mask);
	if (!assign_vector_locked(irqd, vector_searchmask))
		return 0;
	/* Try the full online mask */
	return assign_vector_locked(irqd, cpu_online_mask);
}