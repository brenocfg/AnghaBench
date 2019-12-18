#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imc_pmu_ref {scalar_t__ refc; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_init; } ;
struct TYPE_4__ {TYPE_1__ pmu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_CORE ; 
 int /*<<< orphan*/  core_imc_cpumask ; 
 TYPE_2__* core_imc_pmu ; 
 struct imc_pmu_ref* core_imc_refc ; 
 int /*<<< orphan*/  cpu_sibling_mask (unsigned int) ; 
 int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int cpumask_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (unsigned int) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  opal_imc_counters_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (TYPE_1__*,unsigned int,int) ; 
 unsigned int threads_per_core ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ppc_core_imc_cpu_offline(unsigned int cpu)
{
	unsigned int core_id;
	int ncpu;
	struct imc_pmu_ref *ref;

	/*
	 * clear this cpu out of the mask, if not present in the mask,
	 * don't bother doing anything.
	 */
	if (!cpumask_test_and_clear_cpu(cpu, &core_imc_cpumask))
		return 0;

	/*
	 * Check whether core_imc is registered. We could end up here
	 * if the cpuhotplug callback registration fails. i.e, callback
	 * invokes the offline path for all sucessfully registered cpus.
	 * At this stage, core_imc pmu will not be registered and we
	 * should return here.
	 *
	 * We return with a zero since this is not an offline failure.
	 * And cpuhp_setup_state() returns the actual failure reason
	 * to the caller, which inturn will call the cleanup routine.
	 */
	if (!core_imc_pmu->pmu.event_init)
		return 0;

	/* Find any online cpu in that core except the current "cpu" */
	ncpu = cpumask_last(cpu_sibling_mask(cpu));

	if (unlikely(ncpu == cpu))
		ncpu = cpumask_any_but(cpu_sibling_mask(cpu), cpu);

	if (ncpu >= 0 && ncpu < nr_cpu_ids) {
		cpumask_set_cpu(ncpu, &core_imc_cpumask);
		perf_pmu_migrate_context(&core_imc_pmu->pmu, cpu, ncpu);
	} else {
		/*
		 * If this is the last cpu in this core then, skip taking refernce
		 * count mutex lock for this core and directly zero "refc" for
		 * this core.
		 */
		opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
				       get_hard_smp_processor_id(cpu));
		core_id = cpu / threads_per_core;
		ref = &core_imc_refc[core_id];
		if (!ref)
			return -EINVAL;

		ref->refc = 0;
	}
	return 0;
}