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
struct cluster_mask {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cluster_masks ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cpumask_var (struct cluster_mask*) ; 
 int /*<<< orphan*/  ipi_mask ; 
 struct cluster_mask* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int x2apic_dead_cpu(unsigned int dead_cpu)
{
	struct cluster_mask *cmsk = per_cpu(cluster_masks, dead_cpu);

	if (cmsk)
		cpumask_clear_cpu(dead_cpu, &cmsk->mask);
	free_cpumask_var(per_cpu(ipi_mask, dead_cpu));
	return 0;
}