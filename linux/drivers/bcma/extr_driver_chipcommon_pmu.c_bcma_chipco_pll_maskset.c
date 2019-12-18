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
typedef  int /*<<< orphan*/  u32 ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU_PLLCTL_ADDR ; 
 int /*<<< orphan*/  BCMA_CC_PMU_PLLCTL_DATA ; 
 int /*<<< orphan*/  bcma_pmu_maskset32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bcma_chipco_pll_maskset(struct bcma_drv_cc *cc, u32 offset, u32 mask,
			     u32 set)
{
	bcma_pmu_write32(cc, BCMA_CC_PMU_PLLCTL_ADDR, offset);
	bcma_pmu_read32(cc, BCMA_CC_PMU_PLLCTL_ADDR);
	bcma_pmu_maskset32(cc, BCMA_CC_PMU_PLLCTL_DATA, mask, set);
}