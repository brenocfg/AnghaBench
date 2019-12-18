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
 int /*<<< orphan*/  cpu_mask ; 
 int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int nr_cpumask_bits ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  pmu_class ; 
 int /*<<< orphan*/  topology_sibling_cpumask (unsigned int) ; 

__attribute__((used)) static int power_cpu_exit(unsigned int cpu)
{
	int target;

	if (!cpumask_test_and_clear_cpu(cpu, &cpu_mask))
		return 0;

	/*
	 * Find a new CPU on the same compute unit, if was set in cpumask
	 * and still some CPUs on compute unit. Then migrate event and
	 * context to new CPU.
	 */
	target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
	if (target < nr_cpumask_bits) {
		cpumask_set_cpu(target, &cpu_mask);
		perf_pmu_migrate_context(&pmu_class, cpu, target);
	}
	return 0;
}