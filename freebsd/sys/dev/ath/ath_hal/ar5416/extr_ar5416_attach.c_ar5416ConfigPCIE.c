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
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah_ini_pcieserdes; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah_ispcie; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH5416 (struct ath_hal*) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL_ENA ; 
 int /*<<< orphan*/  AR_WA ; 
 int /*<<< orphan*/  AR_WA_DEFAULT ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_ini_write (struct ath_hal*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5416ConfigPCIE(struct ath_hal *ah, HAL_BOOL restore, HAL_BOOL power_off)
{

	/* This is only applicable for AR5418 (AR5416 PCIe) */
	if (! AH_PRIVATE(ah)->ah_ispcie)
		return;

	if (! restore) {
		ath_hal_ini_write(ah, &AH5416(ah)->ah_ini_pcieserdes, 1, 0);
		OS_DELAY(1000);
	}

	if (power_off) {		/* Power-off */
		/* clear bit 19 to disable L1 */
		OS_REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
	} else {			/* Power-on */
		/* Set default WAR values for Owl */
		OS_REG_WRITE(ah, AR_WA, AR_WA_DEFAULT);

		/* set bit 19 to allow forcing of pcie core into L1 state */
		OS_REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
	}
}