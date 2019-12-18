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
struct rapl_pmu {int cpu; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 struct rapl_pmu* cpu_to_rapl_pmu (unsigned int) ; 
 int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  rapl_cpu_mask ; 
 int /*<<< orphan*/  topology_die_cpumask (unsigned int) ; 

__attribute__((used)) static int rapl_cpu_offline(unsigned int cpu)
{
	struct rapl_pmu *pmu = cpu_to_rapl_pmu(cpu);
	int target;

	/* Check if exiting cpu is used for collecting rapl events */
	if (!cpumask_test_and_clear_cpu(cpu, &rapl_cpu_mask))
		return 0;

	pmu->cpu = -1;
	/* Find a new cpu to collect rapl events */
	target = cpumask_any_but(topology_die_cpumask(cpu), cpu);

	/* Migrate rapl events to the new target */
	if (target < nr_cpu_ids) {
		cpumask_set_cpu(target, &rapl_cpu_mask);
		pmu->cpu = target;
		perf_pmu_migrate_context(pmu->pmu, cpu, target);
	}
	return 0;
}