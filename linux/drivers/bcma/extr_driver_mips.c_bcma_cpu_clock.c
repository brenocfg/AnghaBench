#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bcma_drv_mips {TYPE_1__* core; } ;
struct TYPE_4__ {int capabilities; } ;
struct bcma_bus {TYPE_2__ drv_cc; } ;
struct TYPE_3__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CC_CAP_PMU ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*) ; 
 int /*<<< orphan*/  bcma_pmu_get_cpu_clock (TYPE_2__*) ; 

u32 bcma_cpu_clock(struct bcma_drv_mips *mcore)
{
	struct bcma_bus *bus = mcore->core->bus;

	if (bus->drv_cc.capabilities & BCMA_CC_CAP_PMU)
		return bcma_pmu_get_cpu_clock(&bus->drv_cc);

	bcma_err(bus, "No PMU available, need this to get the cpu clock\n");
	return 0;
}