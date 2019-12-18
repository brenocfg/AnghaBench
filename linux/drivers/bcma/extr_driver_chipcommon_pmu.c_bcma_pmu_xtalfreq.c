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
typedef  int u32 ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU_STAT ; 
 int BCMA_CC_PMU_STAT_EXT_LPO_AVAIL ; 
 int /*<<< orphan*/  BCMA_CC_PMU_XTAL_FREQ ; 
 int BCMA_CC_PMU_XTAL_FREQ_ILPCTL_MASK ; 
 int /*<<< orphan*/  BCMA_CC_PMU_XTAL_FREQ_MEASURE_SHIFT ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int bcma_pmu_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_write32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u32 bcma_pmu_xtalfreq(struct bcma_drv_cc *cc)
{
	u32 ilp_ctl, alp_hz;

	if (!(bcma_pmu_read32(cc, BCMA_CC_PMU_STAT) &
	      BCMA_CC_PMU_STAT_EXT_LPO_AVAIL))
		return 0;

	bcma_pmu_write32(cc, BCMA_CC_PMU_XTAL_FREQ,
			 BIT(BCMA_CC_PMU_XTAL_FREQ_MEASURE_SHIFT));
	usleep_range(1000, 2000);

	ilp_ctl = bcma_pmu_read32(cc, BCMA_CC_PMU_XTAL_FREQ);
	ilp_ctl &= BCMA_CC_PMU_XTAL_FREQ_ILPCTL_MASK;

	bcma_pmu_write32(cc, BCMA_CC_PMU_XTAL_FREQ, 0);

	alp_hz = ilp_ctl * 32768 / 4;
	return (alp_hz + 50000) / 100000 * 100;
}