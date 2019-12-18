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
struct perf_event {int dummy; } ;
struct imc_pmu_ref {scalar_t__ refc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_CORE ; 
 int /*<<< orphan*/  SPRN_LDBAR ; 
 struct imc_pmu_ref* core_imc_refc ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (int) ; 
 int /*<<< orphan*/  imc_event_update (struct perf_event*) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ opal_imc_counters_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int smp_processor_id () ; 
 int threads_per_core ; 

__attribute__((used)) static void thread_imc_event_del(struct perf_event *event, int flags)
{

	int core_id;
	struct imc_pmu_ref *ref;

	mtspr(SPRN_LDBAR, 0);

	core_id = smp_processor_id() / threads_per_core;
	ref = &core_imc_refc[core_id];

	mutex_lock(&ref->lock);
	ref->refc--;
	if (ref->refc == 0) {
		if (opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
		    get_hard_smp_processor_id(smp_processor_id()))) {
			mutex_unlock(&ref->lock);
			pr_err("thread-imc: Unable to stop the counters\
				for core %d\n", core_id);
			return;
		}
	} else if (ref->refc < 0) {
		ref->refc = 0;
	}
	mutex_unlock(&ref->lock);
	/*
	 * Take a snapshot and calculate the delta and update
	 * the event counter values.
	 */
	imc_event_update(event);
}