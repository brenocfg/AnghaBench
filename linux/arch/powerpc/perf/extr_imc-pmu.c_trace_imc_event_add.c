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
 int /*<<< orphan*/  OPAL_IMC_COUNTERS_TRACE ; 
 int /*<<< orphan*/  SPRN_LDBAR ; 
 int THREAD_IMC_LDBAR_MASK ; 
 int TRACE_IMC_ENABLE ; 
 struct imc_pmu_ref* core_imc_refc ; 
 int /*<<< orphan*/  get_hard_smp_processor_id (int) ; 
 int get_trace_imc_event_base_addr () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ opal_imc_counters_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int smp_processor_id () ; 
 int threads_per_core ; 
 struct imc_pmu_ref* trace_imc_refc ; 

__attribute__((used)) static int trace_imc_event_add(struct perf_event *event, int flags)
{
	int core_id = smp_processor_id() / threads_per_core;
	struct imc_pmu_ref *ref = NULL;
	u64 local_mem, ldbar_value;

	/* Set trace-imc bit in ldbar and load ldbar with per-thread memory address */
	local_mem = get_trace_imc_event_base_addr();
	ldbar_value = ((u64)local_mem & THREAD_IMC_LDBAR_MASK) | TRACE_IMC_ENABLE;

	if (core_imc_refc)
		ref = &core_imc_refc[core_id];
	if (!ref) {
		/* If core-imc is not enabled, use trace-imc reference count */
		if (trace_imc_refc)
			ref = &trace_imc_refc[core_id];
		if (!ref)
			return -EINVAL;
	}
	mtspr(SPRN_LDBAR, ldbar_value);
	mutex_lock(&ref->lock);
	if (ref->refc == 0) {
		if (opal_imc_counters_start(OPAL_IMC_COUNTERS_TRACE,
				get_hard_smp_processor_id(smp_processor_id()))) {
			mutex_unlock(&ref->lock);
			pr_err("trace-imc: Unable to start the counters for core %d\n", core_id);
			mtspr(SPRN_LDBAR, 0);
			return -EINVAL;
		}
	}
	++ref->refc;
	mutex_unlock(&ref->lock);

	return 0;
}