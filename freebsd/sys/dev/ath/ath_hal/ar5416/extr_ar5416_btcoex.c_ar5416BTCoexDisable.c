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
struct ath_hal_5416 {scalar_t__ ah_btCoexSingleAnt; int /*<<< orphan*/  ah_btCoexEnabled; int /*<<< orphan*/  ah_wlanActiveGpioSelect; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_BT_COEX_MODE ; 
 int /*<<< orphan*/  AR_BT_COEX_MODE2 ; 
 int /*<<< orphan*/  AR_BT_COEX_WEIGHT ; 
 int /*<<< orphan*/  AR_BT_COEX_WEIGHT2 ; 
 int AR_BT_MODE ; 
 int AR_BT_QUIET ; 
 int /*<<< orphan*/  AR_MISC_MODE ; 
 int /*<<< orphan*/  AR_PCU_BT_ANT_PREVENT_RX ; 
 int /*<<< orphan*/  AR_QUIET1 ; 
 int /*<<< orphan*/  AR_QUIET1_QUIET_ACK_CTS_ENABLE ; 
 scalar_t__ AR_SREV_9271 (struct ath_hal*) ; 
 scalar_t__ AR_SREV_KIWI_10_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_GPIO_OUTPUT_MUX_AS_OUTPUT ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5416GpioCfgInput (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5416GpioCfgOutput (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5416GpioSet (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5416BTCoexDisable(struct ath_hal *ah)
{
	struct ath_hal_5416 *ahp = AH5416(ah);

	/* Always drive rx_clear_external output as 0 */
	ar5416GpioSet(ah, ahp->ah_wlanActiveGpioSelect, 0);
	ar5416GpioCfgOutput(ah, ahp->ah_wlanActiveGpioSelect,
	    HAL_GPIO_OUTPUT_MUX_AS_OUTPUT);

	if (AR_SREV_9271(ah)) {
		/*
		 * Set wlanActiveGpio to input when disabling BT-COEX to
		 * reduce power consumption
		 */
		ar5416GpioCfgInput(ah, ahp->ah_wlanActiveGpioSelect);
	}

	if (ahp->ah_btCoexSingleAnt == AH_TRUE) {
		OS_REG_RMW_FIELD(ah, AR_QUIET1, AR_QUIET1_QUIET_ACK_CTS_ENABLE,
		    1);
		OS_REG_RMW_FIELD(ah, AR_MISC_MODE, AR_PCU_BT_ANT_PREVENT_RX,
		    0);
	}

	OS_REG_WRITE(ah, AR_BT_COEX_MODE, AR_BT_QUIET | AR_BT_MODE);
	OS_REG_WRITE(ah, AR_BT_COEX_WEIGHT, 0);
	if (AR_SREV_KIWI_10_OR_LATER(ah))
		OS_REG_WRITE(ah, AR_BT_COEX_WEIGHT2, 0);
	OS_REG_WRITE(ah, AR_BT_COEX_MODE2, 0);

	ahp->ah_btCoexEnabled = AH_FALSE;
}