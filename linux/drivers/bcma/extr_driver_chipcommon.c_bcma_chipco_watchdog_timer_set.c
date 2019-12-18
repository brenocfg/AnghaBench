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
typedef  int u32 ;
struct bcma_drv_cc {TYPE_2__* core; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct bcma_bus {TYPE_1__ chipinfo; } ;
struct TYPE_4__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU_WATCHDOG ; 
 int /*<<< orphan*/  BCMA_CC_WATCHDOG ; 
 scalar_t__ BCMA_CHIP_ID_BCM4707 ; 
 scalar_t__ BCMA_CHIP_ID_BCM47094 ; 
 scalar_t__ BCMA_CHIP_ID_BCM53018 ; 
 int /*<<< orphan*/  BCMA_CLKMODE_DYNAMIC ; 
 int /*<<< orphan*/  BCMA_CLKMODE_FAST ; 
 int /*<<< orphan*/  bcma_cc_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 
 int bcma_chipco_watchdog_get_max_timer (struct bcma_drv_cc*) ; 
 scalar_t__ bcma_core_cc_has_pmu_watchdog (struct bcma_drv_cc*) ; 
 int /*<<< orphan*/  bcma_core_set_clockmode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int) ; 

u32 bcma_chipco_watchdog_timer_set(struct bcma_drv_cc *cc, u32 ticks)
{
	u32 maxt;

	maxt = bcma_chipco_watchdog_get_max_timer(cc);
	if (bcma_core_cc_has_pmu_watchdog(cc)) {
		if (ticks == 1)
			ticks = 2;
		else if (ticks > maxt)
			ticks = maxt;
		bcma_pmu_write32(cc, BCMA_CC_PMU_WATCHDOG, ticks);
	} else {
		struct bcma_bus *bus = cc->core->bus;

		if (bus->chipinfo.id != BCMA_CHIP_ID_BCM4707 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM47094 &&
		    bus->chipinfo.id != BCMA_CHIP_ID_BCM53018)
			bcma_core_set_clockmode(cc->core,
						ticks ? BCMA_CLKMODE_FAST : BCMA_CLKMODE_DYNAMIC);

		if (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		bcma_cc_write32(cc, BCMA_CC_WATCHDOG, ticks);
	}
	return ticks;
}