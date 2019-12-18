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
struct nds32_pmu {int /*<<< orphan*/  name; int /*<<< orphan*/  pmu; int /*<<< orphan*/  num_events; TYPE_1__* plat_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nds32_init (struct nds32_pmu*) ; 
 int perf_pmu_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nds32_pmu_register(struct nds32_pmu *nds32_pmu, int type)
{
	nds32_init(nds32_pmu);
	pm_runtime_enable(&nds32_pmu->plat_device->dev);
	pr_info("enabled with %s PMU driver, %d counters available\n",
		nds32_pmu->name, nds32_pmu->num_events);
	return perf_pmu_register(&nds32_pmu->pmu, nds32_pmu->name, type);
}