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
struct imc_pmu_ref {scalar_t__ refc; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_NEST ; 
 int cpu_to_node (unsigned int) ; 
 int cpumask_any_but (struct cpumask const*,unsigned int) ; 
 int cpumask_last (struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_and_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (unsigned int) ; 
 struct imc_pmu_ref* get_nest_pmu_ref (unsigned int) ; 
 int /*<<< orphan*/  nest_change_cpu_context (unsigned int,int) ; 
 int /*<<< orphan*/  nest_imc_cpumask ; 
 int /*<<< orphan*/  nest_pmus ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  opal_imc_counters_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ppc_nest_imc_cpu_offline(unsigned int cpu)
{
	int nid, target = -1;
	const struct cpumask *l_cpumask;
	struct imc_pmu_ref *ref;

	/*
	 * Check in the designated list for this cpu. Dont bother
	 * if not one of them.
	 */
	if (!cpumask_test_and_clear_cpu(cpu, &nest_imc_cpumask))
		return 0;

	/*
	 * Check whether nest_imc is registered. We could end up here if the
	 * cpuhotplug callback registration fails. i.e, callback invokes the
	 * offline path for all successfully registered nodes. At this stage,
	 * nest_imc pmu will not be registered and we should return here.
	 *
	 * We return with a zero since this is not an offline failure. And
	 * cpuhp_setup_state() returns the actual failure reason to the caller,
	 * which in turn will call the cleanup routine.
	 */
	if (!nest_pmus)
		return 0;

	/*
	 * Now that this cpu is one of the designated,
	 * find a next cpu a) which is online and b) in same chip.
	 */
	nid = cpu_to_node(cpu);
	l_cpumask = cpumask_of_node(nid);
	target = cpumask_last(l_cpumask);

	/*
	 * If this(target) is the last cpu in the cpumask for this chip,
	 * check for any possible online cpu in the chip.
	 */
	if (unlikely(target == cpu))
		target = cpumask_any_but(l_cpumask, cpu);

	/*
	 * Update the cpumask with the target cpu and
	 * migrate the context if needed
	 */
	if (target >= 0 && target < nr_cpu_ids) {
		cpumask_set_cpu(target, &nest_imc_cpumask);
		nest_change_cpu_context(cpu, target);
	} else {
		opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
				       get_hard_smp_processor_id(cpu));
		/*
		 * If this is the last cpu in this chip then, skip the reference
		 * count mutex lock and make the reference count on this chip zero.
		 */
		ref = get_nest_pmu_ref(cpu);
		if (!ref)
			return -EINVAL;

		ref->refc = 0;
	}
	return 0;
}