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
struct rapl_pmu {unsigned int cpu; int /*<<< orphan*/  timer_interval; int /*<<< orphan*/ * pmu; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct rapl_pmu** pmus; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 struct rapl_pmu* cpu_to_rapl_pmu (unsigned int) ; 
 int cpumask_any_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 struct rapl_pmu* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  rapl_cpu_mask ; 
 int /*<<< orphan*/  rapl_hrtimer_init (struct rapl_pmu*) ; 
 TYPE_1__* rapl_pmus ; 
 int /*<<< orphan*/  rapl_timer_ms ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  topology_die_cpumask (unsigned int) ; 
 size_t topology_logical_die_id (unsigned int) ; 

__attribute__((used)) static int rapl_cpu_online(unsigned int cpu)
{
	struct rapl_pmu *pmu = cpu_to_rapl_pmu(cpu);
	int target;

	if (!pmu) {
		pmu = kzalloc_node(sizeof(*pmu), GFP_KERNEL, cpu_to_node(cpu));
		if (!pmu)
			return -ENOMEM;

		raw_spin_lock_init(&pmu->lock);
		INIT_LIST_HEAD(&pmu->active_list);
		pmu->pmu = &rapl_pmus->pmu;
		pmu->timer_interval = ms_to_ktime(rapl_timer_ms);
		rapl_hrtimer_init(pmu);

		rapl_pmus->pmus[topology_logical_die_id(cpu)] = pmu;
	}

	/*
	 * Check if there is an online cpu in the package which collects rapl
	 * events already.
	 */
	target = cpumask_any_and(&rapl_cpu_mask, topology_die_cpumask(cpu));
	if (target < nr_cpu_ids)
		return 0;

	cpumask_set_cpu(cpu, &rapl_cpu_mask);
	pmu->cpu = cpu;
	return 0;
}