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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah_ini_pcieserdes; } ;
struct TYPE_3__ {scalar_t__ ah_ispcie; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH5416 (struct ath_hal*) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int AR9280_WA_DEFAULT ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL_ENA ; 
 int /*<<< orphan*/  AR_WA ; 
 int AR_WA_BIT22 ; 
 int AR_WA_BIT6 ; 
 int AR_WA_BIT7 ; 
 int AR_WA_D3_L1_DISABLE ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_ini_write (struct ath_hal*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar9280ConfigPCIE(struct ath_hal *ah, HAL_BOOL restore, HAL_BOOL power_off)
{
	uint32_t val;

	if (AH_PRIVATE(ah)->ah_ispcie && !restore) {
		ath_hal_ini_write(ah, &AH5416(ah)->ah_ini_pcieserdes, 1, 0);
		OS_DELAY(1000);
	}


	/*
	 * Set PCIe workaround bits
	 *
	 * NOTE:
	 *
	 * In Merlin and Kite, bit 14 in WA register (disable L1) should only
	 * be set when device enters D3 and be cleared when device comes back
	 * to D0.
	 */
	if (power_off) {		/* Power-off */
		OS_REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);

		val = OS_REG_READ(ah, AR_WA);

		/*
		 * Disable bit 6 and 7 before entering D3 to prevent
		 * system hang.
		 */
		val &= ~(AR_WA_BIT6 | AR_WA_BIT7);

		/*
		 * XXX Not sure, is specified in the reference HAL.
		 */
		val |= AR_WA_BIT22;

		/*
		 * See above: set AR_WA_D3_L1_DISABLE when entering D3 state.
		 *
		 * XXX The reference HAL does it this way - it only sets
		 * AR_WA_D3_L1_DISABLE if it's set in AR9280_WA_DEFAULT,
		 * which it (currently) isn't.  So the following statement
		 * is currently a NOP.
		 */
		if (AR9280_WA_DEFAULT & AR_WA_D3_L1_DISABLE)
			val |= AR_WA_D3_L1_DISABLE;

		OS_REG_WRITE(ah, AR_WA, val);
	} else {			/* Power-on */
		val = AR9280_WA_DEFAULT;

		/*
		 * See note above: make sure L1_DISABLE is not set.
		 */
		val &= (~AR_WA_D3_L1_DISABLE);
		OS_REG_WRITE(ah, AR_WA, val);

		/* set bit 19 to allow forcing of pcie core into L1 state */
		OS_REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
	}
}