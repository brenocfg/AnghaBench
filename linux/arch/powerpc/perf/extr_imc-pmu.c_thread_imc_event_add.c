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
typedef  int u64 ;
struct perf_event {int dummy; } ;
struct imc_pmu_ref {scalar_t__ refc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_CORE ; 
 int PERF_EF_START ; 
 int /*<<< orphan*/  SPRN_LDBAR ; 
 int THREAD_IMC_ENABLE ; 
 int THREAD_IMC_LDBAR_MASK ; 
 struct imc_pmu_ref* core_imc_refc ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (int) ; 
 int /*<<< orphan*/  imc_event_start (struct perf_event*,int) ; 
 int /*<<< orphan*/  is_core_imc_mem_inited (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ opal_imc_counters_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  thread_imc_mem ; 
 int threads_per_core ; 

__attribute__((used)) static int thread_imc_event_add(struct perf_event *event, int flags)
{
	int core_id;
	struct imc_pmu_ref *ref;
	u64 ldbar_value, *local_mem = per_cpu(thread_imc_mem, smp_processor_id());

	if (flags & PERF_EF_START)
		imc_event_start(event, flags);

	if (!is_core_imc_mem_inited(smp_processor_id()))
		return -EINVAL;

	core_id = smp_processor_id() / threads_per_core;
	ldbar_value = ((u64)local_mem & THREAD_IMC_LDBAR_MASK) | THREAD_IMC_ENABLE;
	mtspr(SPRN_LDBAR, ldbar_value);

	/*
	 * imc pmus are enabled only when it is used.
	 * See if this is triggered for the first time.
	 * If yes, take the mutex lock and enable the counters.
	 * If not, just increment the count in ref count struct.
	 */
	ref = &core_imc_refc[core_id];
	if (!ref)
		return -EINVAL;

	mutex_lock(&ref->lock);
	if (ref->refc == 0) {
		if (opal_imc_counters_start(OPAL_IMC_COUNTERS_CORE,
		    get_hard_smp_processor_id(smp_processor_id()))) {
			mutex_unlock(&ref->lock);
			pr_err("thread-imc: Unable to start the counter\
				for core %d\n", core_id);
			return -EINVAL;
		}
	}
	++ref->refc;
	mutex_unlock(&ref->lock);
	return 0;
}