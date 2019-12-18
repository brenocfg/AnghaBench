#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  imc_common_cpuhp_mem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  imc_common_mem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* thread_imc_pmu ; 

void unregister_thread_imc(void)
{
	imc_common_cpuhp_mem_free(thread_imc_pmu);
	imc_common_mem_free(thread_imc_pmu);
	perf_pmu_unregister(&thread_imc_pmu->pmu);
}