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
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2x0_pmu ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pmu_cpu ; 

__attribute__((used)) static int l2x0_pmu_offline_cpu(unsigned int cpu)
{
	unsigned int target;

	if (!cpumask_test_and_clear_cpu(cpu, &pmu_cpu))
		return 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	if (target >= nr_cpu_ids)
		return 0;

	perf_pmu_migrate_context(l2x0_pmu, cpu, target);
	cpumask_set_cpu(target, &pmu_cpu);

	return 0;
}