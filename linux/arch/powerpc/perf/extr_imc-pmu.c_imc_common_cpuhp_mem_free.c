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
struct imc_pmu {scalar_t__ domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE ; 
 int /*<<< orphan*/  CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE ; 
 int /*<<< orphan*/  CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE ; 
 int /*<<< orphan*/  CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE ; 
 scalar_t__ IMC_DOMAIN_CORE ; 
 scalar_t__ IMC_DOMAIN_NEST ; 
 scalar_t__ IMC_DOMAIN_THREAD ; 
 scalar_t__ IMC_DOMAIN_TRACE ; 
 int /*<<< orphan*/  cleanup_all_core_imc_memory () ; 
 int /*<<< orphan*/  cleanup_all_thread_imc_memory () ; 
 int /*<<< orphan*/  cleanup_all_trace_imc_memory () ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nest_imc_refc ; 
 int /*<<< orphan*/  nest_init_lock ; 
 int nest_pmus ; 
 int /*<<< orphan*/ * per_nest_pmu_arr ; 

__attribute__((used)) static void imc_common_cpuhp_mem_free(struct imc_pmu *pmu_ptr)
{
	if (pmu_ptr->domain == IMC_DOMAIN_NEST) {
		mutex_lock(&nest_init_lock);
		if (nest_pmus == 1) {
			cpuhp_remove_state(CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE);
			kfree(nest_imc_refc);
			kfree(per_nest_pmu_arr);
			per_nest_pmu_arr = NULL;
		}

		if (nest_pmus > 0)
			nest_pmus--;
		mutex_unlock(&nest_init_lock);
	}

	/* Free core_imc memory */
	if (pmu_ptr->domain == IMC_DOMAIN_CORE) {
		cpuhp_remove_state(CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE);
		cleanup_all_core_imc_memory();
	}

	/* Free thread_imc memory */
	if (pmu_ptr->domain == IMC_DOMAIN_THREAD) {
		cpuhp_remove_state(CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE);
		cleanup_all_thread_imc_memory();
	}

	if (pmu_ptr->domain == IMC_DOMAIN_TRACE) {
		cpuhp_remove_state(CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE);
		cleanup_all_trace_imc_memory();
	}
}