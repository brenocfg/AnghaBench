#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int halLow5GhzChan; int halHigh5GhzChan; int halNumMRRetries; int halNumTxMaps; int halKeyCacheSize; int halTxTstampPrecision; int halRxTstampPrecision; int halIntrMask; void* halHasRxSelfLinkedTail; void* hal4kbSplitTransSupport; void* halRfSilentSupport; void* halUseCombinedRadarRssi; void* halChanQuarterRate; void* halChanHalfRate; int /*<<< orphan*/  halTotalQueues; void* halPSPollBroken; void* halSleepAfterBeaconBroken; int /*<<< orphan*/  halWirelessModes; } ;
struct ath_hal_private {int ah_rfsilent; void* ah_rxornIsFatal; void* ah_rfkillEnabled; TYPE_1__ ah_caps; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 void* AH_TRUE ; 
 int /*<<< orphan*/  AR_EEPROM_RFSILENT_GPIO_SEL ; 
 int /*<<< orphan*/  AR_EEPROM_RFSILENT_POLARITY ; 
 int /*<<< orphan*/  AR_EEP_RFKILL ; 
 int HAL_INT_BNR ; 
 int HAL_INT_COMMON ; 
 int HAL_INT_FATAL ; 
 int HAL_INT_RX ; 
 int HAL_INT_TX ; 
 int /*<<< orphan*/  HAL_MODE_11A ; 
 int /*<<< orphan*/  HAL_NUM_TX_QUEUES ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HAL_BOOL
ar5210FillCapabilityInfo(struct ath_hal *ah)
{
	struct ath_hal_private *ahpriv = AH_PRIVATE(ah);
	HAL_CAPABILITIES *pCap = &ahpriv->ah_caps;

	pCap->halWirelessModes |= HAL_MODE_11A;

	pCap->halLow5GhzChan = 5120;
	pCap->halHigh5GhzChan = 5430;

	pCap->halSleepAfterBeaconBroken = AH_TRUE;
	pCap->halPSPollBroken = AH_FALSE;
	pCap->halNumMRRetries = 1;		/* No hardware MRR support */
	pCap->halNumTxMaps = 1;			/* Single TX ptr per descr */

	pCap->halTotalQueues = HAL_NUM_TX_QUEUES;
	pCap->halKeyCacheSize = 64;

	/* XXX not needed */
	pCap->halChanHalfRate = AH_FALSE;
	pCap->halChanQuarterRate = AH_FALSE;

	/*
	 * RSSI uses the combined field; some 11n NICs may use
	 * the control chain RSSI.
	 */
	pCap->halUseCombinedRadarRssi = AH_TRUE;

	if (ath_hal_eepromGetFlag(ah, AR_EEP_RFKILL)) {
		/*
		 * Setup initial rfsilent settings based on the EEPROM
		 * contents.  Pin 0, polarity 0 is fixed; record this
		 * using the EEPROM format found in later parts.
		 */
		ahpriv->ah_rfsilent = SM(0, AR_EEPROM_RFSILENT_GPIO_SEL)
				    | SM(0, AR_EEPROM_RFSILENT_POLARITY);
		ahpriv->ah_rfkillEnabled = AH_TRUE;
		pCap->halRfSilentSupport = AH_TRUE;
	}

	pCap->halTxTstampPrecision = 16;
	pCap->halRxTstampPrecision = 15;	/* NB: s/w extended from 13 */
	pCap->halIntrMask = (HAL_INT_COMMON - HAL_INT_BNR)
			| HAL_INT_RX
			| HAL_INT_TX
			| HAL_INT_FATAL
			;

	pCap->hal4kbSplitTransSupport = AH_TRUE;
	pCap->halHasRxSelfLinkedTail = AH_TRUE;

	ahpriv->ah_rxornIsFatal = AH_TRUE;
	return AH_TRUE;
}