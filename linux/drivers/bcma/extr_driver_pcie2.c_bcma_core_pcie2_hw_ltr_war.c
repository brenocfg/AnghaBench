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
typedef  int u8 ;
typedef  int u32 ;
struct bcma_drv_pcie2 {TYPE_2__* core; } ;
struct TYPE_3__ {int rev; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDADDR ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDDATA ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE2_LTR_STATE ; 
 int PCIE2_CAP_DEVSTSCTRL2_LTRENAB ; 
 int PCIE2_CAP_DEVSTSCTRL2_OFFSET ; 
 int PCIE2_LTR_ACTIVE ; 
 int PCIE2_LTR_SLEEP ; 
 int /*<<< orphan*/  bcma_core_pcie2_set_ltr_vals (struct bcma_drv_pcie2*) ; 
 int pcie2_read32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie2_write32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void bcma_core_pcie2_hw_ltr_war(struct bcma_drv_pcie2 *pcie2)
{
	u8 core_rev = pcie2->core->id.rev;
	u32 devstsctr2;

	if (core_rev < 2 || core_rev == 10 || core_rev > 13)
		return;

	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
		      PCIE2_CAP_DEVSTSCTRL2_OFFSET);
	devstsctr2 = pcie2_read32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA);
	if (devstsctr2 & PCIE2_CAP_DEVSTSCTRL2_LTRENAB) {
		/* force the right LTR values */
		bcma_core_pcie2_set_ltr_vals(pcie2);

		/* TODO:
		 *si_core_wrapperreg(pcie2, 3, 0x60, 0x8080, 0);
		 */

		/* enable the LTR */
		devstsctr2 |= PCIE2_CAP_DEVSTSCTRL2_LTRENAB;
		pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR,
			      PCIE2_CAP_DEVSTSCTRL2_OFFSET);
		pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, devstsctr2);

		/* set the LTR state to be active */
		pcie2_write32(pcie2, BCMA_CORE_PCIE2_LTR_STATE,
			      PCIE2_LTR_ACTIVE);
		usleep_range(1000, 2000);

		/* set the LTR state to be sleep */
		pcie2_write32(pcie2, BCMA_CORE_PCIE2_LTR_STATE,
			      PCIE2_LTR_SLEEP);
		usleep_range(1000, 2000);
	}
}