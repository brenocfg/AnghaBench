#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ event_base; scalar_t__ sample_period; } ;
struct TYPE_4__ {int config; scalar_t__ type; } ;
struct perf_event {scalar_t__ cpu; int /*<<< orphan*/  destroy; TYPE_3__ hw; TYPE_2__* pmu; TYPE_1__ attr; } ;
struct imc_pmu_ref {scalar_t__ refc; int /*<<< orphan*/  lock; } ;
struct imc_pmu {int counter_mem_size; struct imc_mem_info* mem_info; } ;
struct imc_mem_info {scalar_t__ vbase; int id; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int IMC_EVENT_OFFSET_MASK ; 
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_NEST ; 
 int cpu_to_chip_id (scalar_t__) ; 
 int cpu_to_node (scalar_t__) ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (scalar_t__) ; 
 struct imc_pmu_ref* get_nest_pmu_ref (scalar_t__) ; 
 struct imc_pmu* imc_event_to_pmu (struct perf_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nest_imc_counters_release ; 
 int opal_imc_counters_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int nest_imc_event_init(struct perf_event *event)
{
	int chip_id, rc, node_id;
	u32 l_config, config = event->attr.config;
	struct imc_mem_info *pcni;
	struct imc_pmu *pmu;
	struct imc_pmu_ref *ref;
	bool flag = false;

	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/* Sampling not supported */
	if (event->hw.sample_period)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	pmu = imc_event_to_pmu(event);

	/* Sanity check for config (event offset) */
	if ((config & IMC_EVENT_OFFSET_MASK) > pmu->counter_mem_size)
		return -EINVAL;

	/*
	 * Nest HW counter memory resides in a per-chip reserve-memory (HOMER).
	 * Get the base memory addresss for this cpu.
	 */
	chip_id = cpu_to_chip_id(event->cpu);

	/* Return, if chip_id is not valid */
	if (chip_id < 0)
		return -ENODEV;

	pcni = pmu->mem_info;
	do {
		if (pcni->id == chip_id) {
			flag = true;
			break;
		}
		pcni++;
	} while (pcni->vbase != 0);

	if (!flag)
		return -ENODEV;

	/*
	 * Add the event offset to the base address.
	 */
	l_config = config & IMC_EVENT_OFFSET_MASK;
	event->hw.event_base = (u64)pcni->vbase + l_config;
	node_id = cpu_to_node(event->cpu);

	/*
	 * Get the imc_pmu_ref struct for this node.
	 * Take the mutex lock and then increment the count of nest pmu events
	 * inited.
	 */
	ref = get_nest_pmu_ref(event->cpu);
	if (!ref)
		return -EINVAL;

	mutex_lock(&ref->lock);
	if (ref->refc == 0) {
		rc = opal_imc_counters_start(OPAL_IMC_COUNTERS_NEST,
					     get_hard_smp_processor_id(event->cpu));
		if (rc) {
			mutex_unlock(&ref->lock);
			pr_err("nest-imc: Unable to start the counters for node %d\n",
									node_id);
			return rc;
		}
	}
	++ref->refc;
	mutex_unlock(&ref->lock);

	event->destroy = nest_imc_counters_release;
	return 0;
}