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
struct bcma_drv_cc {TYPE_1__* core; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_3__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_CHIPSTAT ; 
 int BCMA_CC_PMU4716_MAINPLL_PLL0 ; 
 scalar_t__ BCMA_CC_PPL_M14_OFF ; 
 int BCMA_CC_PPL_MDIV_MASK ; 
 int BCMA_CC_PPL_MDIV_WIDTH ; 
 int BCMA_CC_PPL_NDIV_MASK ; 
 int BCMA_CC_PPL_NDIV_SHIFT ; 
 scalar_t__ BCMA_CC_PPL_NM5_OFF ; 
 scalar_t__ BCMA_CC_PPL_P1P2_OFF ; 
 int BCMA_CC_PPL_P1_MASK ; 
 int BCMA_CC_PPL_P1_SHIFT ; 
 int BCMA_CC_PPL_P2_MASK ; 
 int BCMA_CC_PPL_P2_SHIFT ; 
 scalar_t__ BCMA_CHIP_ID_BCM4749 ; 
 scalar_t__ BCMA_CHIP_ID_BCM5357 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int bcma_chipco_pll_read (struct bcma_drv_cc*,scalar_t__) ; 
 int bcma_pmu_get_alp_clock (struct bcma_drv_cc*) ; 

__attribute__((used)) static u32 bcma_pmu_pll_clock(struct bcma_drv_cc *cc, u32 pll0, u32 m)
{
	u32 tmp, div, ndiv, p1, p2, fc;
	struct bcma_bus *bus = cc->core->bus;

	BUG_ON((pll0 & 3) || (pll0 > BCMA_CC_PMU4716_MAINPLL_PLL0));

	BUG_ON(!m || m > 4);

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM4749) {
		/* Detect failure in clock setting */
		tmp = bcma_cc_read32(cc, BCMA_CC_CHIPSTAT);
		if (tmp & 0x40000)
			return 133 * 1000000;
	}

	tmp = bcma_chipco_pll_read(cc, pll0 + BCMA_CC_PPL_P1P2_OFF);
	p1 = (tmp & BCMA_CC_PPL_P1_MASK) >> BCMA_CC_PPL_P1_SHIFT;
	p2 = (tmp & BCMA_CC_PPL_P2_MASK) >> BCMA_CC_PPL_P2_SHIFT;

	tmp = bcma_chipco_pll_read(cc, pll0 + BCMA_CC_PPL_M14_OFF);
	div = (tmp >> ((m - 1) * BCMA_CC_PPL_MDIV_WIDTH)) &
		BCMA_CC_PPL_MDIV_MASK;

	tmp = bcma_chipco_pll_read(cc, pll0 + BCMA_CC_PPL_NM5_OFF);
	ndiv = (tmp & BCMA_CC_PPL_NDIV_MASK) >> BCMA_CC_PPL_NDIV_SHIFT;

	/* Do calculation in Mhz */
	fc = bcma_pmu_get_alp_clock(cc) / 1000000;
	fc = (p1 * ndiv * fc) / p2;

	/* Return clock in Hertz */
	return (fc / div) * 1000000;
}