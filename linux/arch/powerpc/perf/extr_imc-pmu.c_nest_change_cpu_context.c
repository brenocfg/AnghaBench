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
struct imc_pmu {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 struct imc_pmu** per_nest_pmu_arr ; 
 int /*<<< orphan*/  perf_pmu_migrate_context (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void nest_change_cpu_context(int old_cpu, int new_cpu)
{
	struct imc_pmu **pn = per_nest_pmu_arr;

	if (old_cpu < 0 || new_cpu < 0)
		return;

	while (*pn) {
		perf_pmu_migrate_context(&(*pn)->pmu, old_cpu, new_cpu);
		pn++;
	}
}