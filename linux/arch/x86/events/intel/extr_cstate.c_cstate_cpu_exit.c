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
 unsigned int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstate_core_cpu_mask ; 
 int /*<<< orphan*/  cstate_core_pmu ; 
 int /*<<< orphan*/  cstate_pkg_cpu_mask ; 
 int /*<<< orphan*/  cstate_pkg_pmu ; 
 scalar_t__ has_cstate_core ; 
 scalar_t__ has_cstate_pkg ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  topology_die_cpumask (unsigned int) ; 
 int /*<<< orphan*/  topology_sibling_cpumask (unsigned int) ; 

__attribute__((used)) static int cstate_cpu_exit(unsigned int cpu)
{
	unsigned int target;

	if (has_cstate_core &&
	    cpumask_test_and_clear_cpu(cpu, &cstate_core_cpu_mask)) {

		target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
		/* Migrate events if there is a valid target */
		if (target < nr_cpu_ids) {
			cpumask_set_cpu(target, &cstate_core_cpu_mask);
			perf_pmu_migrate_context(&cstate_core_pmu, cpu, target);
		}
	}

	if (has_cstate_pkg &&
	    cpumask_test_and_clear_cpu(cpu, &cstate_pkg_cpu_mask)) {

		target = cpumask_any_but(topology_die_cpumask(cpu), cpu);
		/* Migrate events if there is a valid target */
		if (target < nr_cpu_ids) {
			cpumask_set_cpu(target, &cstate_pkg_cpu_mask);
			perf_pmu_migrate_context(&cstate_pkg_pmu, cpu, target);
		}
	}
	return 0;
}