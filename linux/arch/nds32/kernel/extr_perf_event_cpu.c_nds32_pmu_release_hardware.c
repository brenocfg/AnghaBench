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
struct nds32_pmu {TYPE_1__* plat_device; int /*<<< orphan*/  (* free_irq ) (struct nds32_pmu*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nds32_pmu*) ; 

__attribute__((used)) static void nds32_pmu_release_hardware(struct nds32_pmu *nds32_pmu)
{
	nds32_pmu->free_irq(nds32_pmu);
	pm_runtime_put_sync(&nds32_pmu->plat_device->dev);
}