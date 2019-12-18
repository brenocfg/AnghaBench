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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_NEST ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 scalar_t__ cpumask_and (struct cpumask*,struct cpumask const*,int /*<<< orphan*/ *) ; 
 struct cpumask* cpumask_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (unsigned int) ; 
 int /*<<< orphan*/  nest_imc_cpumask ; 
 int opal_imc_counters_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppc_nest_imc_cpu_online(unsigned int cpu)
{
	const struct cpumask *l_cpumask;
	static struct cpumask tmp_mask;
	int res;

	/* Get the cpumask of this node */
	l_cpumask = cpumask_of_node(cpu_to_node(cpu));

	/*
	 * If this is not the first online CPU on this node, then
	 * just return.
	 */
	if (cpumask_and(&tmp_mask, l_cpumask, &nest_imc_cpumask))
		return 0;

	/*
	 * If this is the first online cpu on this node
	 * disable the nest counters by making an OPAL call.
	 */
	res = opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
				     get_hard_smp_processor_id(cpu));
	if (res)
		return res;

	/* Make this CPU the designated target for counter collection */
	cpumask_set_cpu(cpu, &nest_imc_cpumask);
	return 0;
}