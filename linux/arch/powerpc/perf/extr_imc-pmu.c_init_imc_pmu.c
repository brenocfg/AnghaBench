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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct imc_pmu {int domain; TYPE_1__ pmu; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IMC_DOMAIN_CORE 131 
#define  IMC_DOMAIN_NEST 130 
#define  IMC_DOMAIN_THREAD 129 
#define  IMC_DOMAIN_TRACE 128 
 int /*<<< orphan*/  cleanup_all_core_imc_memory () ; 
 int /*<<< orphan*/  cleanup_all_thread_imc_memory () ; 
 int /*<<< orphan*/  cleanup_all_trace_imc_memory () ; 
 int core_imc_pmu_cpumask_init () ; 
 int /*<<< orphan*/  imc_common_cpuhp_mem_free (struct imc_pmu*) ; 
 int /*<<< orphan*/  imc_common_mem_free (struct imc_pmu*) ; 
 int imc_mem_init (struct imc_pmu*,struct device_node*,int) ; 
 int init_nest_pmu_ref () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nest_imc_refc ; 
 int /*<<< orphan*/  nest_init_lock ; 
 int nest_pmu_cpumask_init () ; 
 int /*<<< orphan*/  nest_pmus ; 
 int /*<<< orphan*/ * per_nest_pmu_arr ; 
 int perf_pmu_register (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int thread_imc_cpu_init () ; 
 int trace_imc_cpu_init () ; 
 int update_events_in_group (struct device_node*,struct imc_pmu*) ; 
 int update_pmu_ops (struct imc_pmu*) ; 

int init_imc_pmu(struct device_node *parent, struct imc_pmu *pmu_ptr, int pmu_idx)
{
	int ret;

	ret = imc_mem_init(pmu_ptr, parent, pmu_idx);
	if (ret)
		goto err_free_mem;

	switch (pmu_ptr->domain) {
	case IMC_DOMAIN_NEST:
		/*
		* Nest imc pmu need only one cpu per chip, we initialize the
		* cpumask for the first nest imc pmu and use the same for the
		* rest. To handle the cpuhotplug callback unregister, we track
		* the number of nest pmus in "nest_pmus".
		*/
		mutex_lock(&nest_init_lock);
		if (nest_pmus == 0) {
			ret = init_nest_pmu_ref();
			if (ret) {
				mutex_unlock(&nest_init_lock);
				kfree(per_nest_pmu_arr);
				per_nest_pmu_arr = NULL;
				goto err_free_mem;
			}
			/* Register for cpu hotplug notification. */
			ret = nest_pmu_cpumask_init();
			if (ret) {
				mutex_unlock(&nest_init_lock);
				kfree(nest_imc_refc);
				kfree(per_nest_pmu_arr);
				per_nest_pmu_arr = NULL;
				goto err_free_mem;
			}
		}
		nest_pmus++;
		mutex_unlock(&nest_init_lock);
		break;
	case IMC_DOMAIN_CORE:
		ret = core_imc_pmu_cpumask_init();
		if (ret) {
			cleanup_all_core_imc_memory();
			goto err_free_mem;
		}

		break;
	case IMC_DOMAIN_THREAD:
		ret = thread_imc_cpu_init();
		if (ret) {
			cleanup_all_thread_imc_memory();
			goto err_free_mem;
		}

		break;
	case IMC_DOMAIN_TRACE:
		ret = trace_imc_cpu_init();
		if (ret) {
			cleanup_all_trace_imc_memory();
			goto err_free_mem;
		}

		break;
	default:
		return  -EINVAL;	/* Unknown domain */
	}

	ret = update_events_in_group(parent, pmu_ptr);
	if (ret)
		goto err_free_cpuhp_mem;

	ret = update_pmu_ops(pmu_ptr);
	if (ret)
		goto err_free_cpuhp_mem;

	ret = perf_pmu_register(&pmu_ptr->pmu, pmu_ptr->pmu.name, -1);
	if (ret)
		goto err_free_cpuhp_mem;

	pr_debug("%s performance monitor hardware support registered\n",
							pmu_ptr->pmu.name);

	return 0;

err_free_cpuhp_mem:
	imc_common_cpuhp_mem_free(pmu_ptr);
err_free_mem:
	imc_common_mem_free(pmu_ptr);
	return ret;
}