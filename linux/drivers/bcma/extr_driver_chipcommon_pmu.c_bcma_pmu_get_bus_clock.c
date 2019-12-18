#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  rev; } ;
struct bcma_drv_cc {TYPE_3__ pmu; TYPE_1__* core; } ;
struct TYPE_5__ {int id; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_4__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU4706_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BCMA_CC_PMU4716_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BCMA_CC_PMU5356_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BCMA_CC_PMU5357_MAINPLL_PLL0 ; 
 int /*<<< orphan*/  BCMA_CC_PMU5_MAINPLL_SSB ; 
 int BCMA_CC_PMU_HT_CLOCK ; 
#define  BCMA_CHIP_ID_BCM4706 135 
#define  BCMA_CHIP_ID_BCM4716 134 
#define  BCMA_CHIP_ID_BCM47162 133 
#define  BCMA_CHIP_ID_BCM4748 132 
#define  BCMA_CHIP_ID_BCM4749 131 
#define  BCMA_CHIP_ID_BCM5356 130 
#define  BCMA_CHIP_ID_BCM5357 129 
#define  BCMA_CHIP_ID_BCM53572 128 
 int bcma_pmu_pll_clock (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcma_pmu_pll_clock_bcm4706 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_warn (struct bcma_bus*,char*,int,int /*<<< orphan*/ ,int) ; 

u32 bcma_pmu_get_bus_clock(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU4716_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM5356:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU5356_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
		return bcma_pmu_pll_clock(cc, BCMA_CC_PMU5357_MAINPLL_PLL0,
					  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM4706:
		return bcma_pmu_pll_clock_bcm4706(cc,
						  BCMA_CC_PMU4706_MAINPLL_PLL0,
						  BCMA_CC_PMU5_MAINPLL_SSB);
	case BCMA_CHIP_ID_BCM53572:
		return 75000000;
	default:
		bcma_warn(bus, "No bus clock specified for %04X device, pmu rev. %d, using default %d Hz\n",
			  bus->chipinfo.id, cc->pmu.rev, BCMA_CC_PMU_HT_CLOCK);
	}
	return BCMA_CC_PMU_HT_CLOCK;
}