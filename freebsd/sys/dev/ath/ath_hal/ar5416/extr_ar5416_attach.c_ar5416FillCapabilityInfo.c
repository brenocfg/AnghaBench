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
typedef  void* uint16_t ;
struct TYPE_2__ {int halWirelessModes; int halLow2GhzChan; int halHigh2GhzChan; int halLow5GhzChan; int halHigh5GhzChan; int halTurboGSupport; int halNumMRRetries; int halNumTxMaps; int halTxTstampPrecision; int halRxTstampPrecision; int halIntrMask; int halNumGpioPins; int halTxStreams; int halRxStreams; int halRtsAggrLimit; int halSerialiseRegWar; void* halRxDoMyBeacon; void* halRfSilentSupport; void* halHasBBReadWar; void* halEnhancedDfsSupport; void* halCSTSupport; void* halGTTSupport; void* halBssidMatchSupport; void* halEnhancedPmSupport; void* halForcePpmSupport; void* halMbssidAggrSupport; scalar_t__ halRxChainMask; scalar_t__ halTxChainMask; void* halHTSupport; void* halNumAntCfg5GHz; void* halNumAntCfg2GHz; void* halHasRxSelfLinkedTail; void* hal4kbSplitTransSupport; void* halAutoSleepSupport; void* halBtCoexSupport; void* halWowMatchPatternExact; void* halWowSupport; void* halFastCCSupport; void* halHwPhyCounterSupport; void* halChanQuarterRate; void* halChanHalfRate; void* halKeyCacheSize; void* halTotalQueues; void* halSpectralScanSupport; void* hal4AddrAggrSupport; void* halTsfAddSupport; void* halMcastKeySrchSupport; void* halBssIdMaskSupport; void* halVEOLSupport; void* halPSPollBroken; void* halTurboPrimeSupport; void* halChapTuningSupport; void* halFastFramesSupport; void* halBurstSupport; void* halCompressSupport; void* halSleepAfterBeaconBroken; void* halChanSpreadSupport; void* halTkipMicTxRxKeySupport; void* halMicAesCcmSupport; void* halMicTkipSupport; void* halMicCkipSupport; void* halCipherAesCcmSupport; void* halCipherTkipSupport; void* halCipherCkipSupport; } ;
struct ath_hal_private {void* ah_rfsilent; int /*<<< orphan*/  ah_ispcie; void* ah_rxornIsFatal; void* ah_rfkillEnabled; TYPE_1__ ah_caps; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 void** AH_NULL ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 void* AH_TRUE ; 
 void* AR5416_KEYTABLE_SIZE ; 
 int /*<<< orphan*/  AR_EEP_AES ; 
 int /*<<< orphan*/  AR_EEP_AMODE ; 
 int /*<<< orphan*/  AR_EEP_GMODE ; 
 int /*<<< orphan*/  AR_EEP_KCENTRIES ; 
 int /*<<< orphan*/  AR_EEP_MAXQCU ; 
 int /*<<< orphan*/  AR_EEP_RFKILL ; 
 int /*<<< orphan*/  AR_EEP_RFSILENT ; 
 int /*<<< orphan*/  AR_EEP_RXMASK ; 
 int /*<<< orphan*/  AR_EEP_TXMASK ; 
 scalar_t__ AR_SREV_OWL (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_FREQ_BAND_2GHZ ; 
 int /*<<< orphan*/  HAL_FREQ_BAND_5GHZ ; 
 int HAL_INT_BMISC ; 
 int HAL_INT_BNR ; 
 int HAL_INT_COMMON ; 
 int HAL_INT_CST ; 
 int HAL_INT_DTIMSYNC ; 
 int HAL_INT_FATAL ; 
 int HAL_INT_GTT ; 
 int HAL_INT_RX ; 
 int HAL_INT_TSFOOR ; 
 int HAL_INT_TX ; 
 int HAL_MODE_108G ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11G ; 
 int HAL_MODE_11NA_HT20 ; 
 int HAL_MODE_11NA_HT40MINUS ; 
 int HAL_MODE_11NA_HT40PLUS ; 
 int HAL_MODE_11NG_HT20 ; 
 int HAL_MODE_11NG_HT40MINUS ; 
 int HAL_MODE_11NG_HT40PLUS ; 
 void* HAL_NUM_TX_QUEUES ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  ahp ; 
 void* ar5416GetNumAntConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_hal_eepromGet (struct ath_hal*,int /*<<< orphan*/ ,void**) ; 
 void* ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int owl_get_ntxchains (scalar_t__) ; 

HAL_BOOL
ar5416FillCapabilityInfo(struct ath_hal *ah)
{
	struct ath_hal_private *ahpriv = AH_PRIVATE(ah);
	HAL_CAPABILITIES *pCap = &ahpriv->ah_caps;
	uint16_t val;
	
	/* Construct wireless mode from EEPROM */
	pCap->halWirelessModes = 0;
	if (ath_hal_eepromGetFlag(ah, AR_EEP_AMODE)) {
		pCap->halWirelessModes |= HAL_MODE_11A
				       |  HAL_MODE_11NA_HT20
				       |  HAL_MODE_11NA_HT40PLUS
				       |  HAL_MODE_11NA_HT40MINUS
				       ;
	}
	if (ath_hal_eepromGetFlag(ah, AR_EEP_GMODE)) {
		pCap->halWirelessModes |= HAL_MODE_11G
				       |  HAL_MODE_11NG_HT20
				       |  HAL_MODE_11NG_HT40PLUS
				       |  HAL_MODE_11NG_HT40MINUS
				       ;
		pCap->halWirelessModes |= HAL_MODE_11A
				       |  HAL_MODE_11NA_HT20
				       |  HAL_MODE_11NA_HT40PLUS
				       |  HAL_MODE_11NA_HT40MINUS
				       ;
	}

	pCap->halLow2GhzChan = 2312;
	pCap->halHigh2GhzChan = 2732;

	pCap->halLow5GhzChan = 4915;
	pCap->halHigh5GhzChan = 6100;

	pCap->halCipherCkipSupport = AH_FALSE;
	pCap->halCipherTkipSupport = AH_TRUE;
	pCap->halCipherAesCcmSupport = ath_hal_eepromGetFlag(ah, AR_EEP_AES);

	pCap->halMicCkipSupport    = AH_FALSE;
	pCap->halMicTkipSupport    = AH_TRUE;
	pCap->halMicAesCcmSupport  = ath_hal_eepromGetFlag(ah, AR_EEP_AES);
	/*
	 * Starting with Griffin TX+RX mic keys can be combined
	 * in one key cache slot.
	 */
	pCap->halTkipMicTxRxKeySupport = AH_TRUE;
	pCap->halChanSpreadSupport = AH_TRUE;
	pCap->halSleepAfterBeaconBroken = AH_TRUE;

	pCap->halCompressSupport = AH_FALSE;
	pCap->halBurstSupport = AH_TRUE;
	pCap->halFastFramesSupport = AH_TRUE;
	pCap->halChapTuningSupport = AH_TRUE;
	pCap->halTurboPrimeSupport = AH_TRUE;

	pCap->halTurboGSupport = pCap->halWirelessModes & HAL_MODE_108G;

	pCap->halPSPollBroken = AH_TRUE;	/* XXX fixed in later revs? */
	pCap->halNumMRRetries = 4;		/* Hardware supports 4 MRR */
	pCap->halNumTxMaps = 1;			/* Single TX ptr per descr */
	pCap->halVEOLSupport = AH_TRUE;
	pCap->halBssIdMaskSupport = AH_TRUE;
	pCap->halMcastKeySrchSupport = AH_TRUE;	/* Works on AR5416 and later */
	pCap->halTsfAddSupport = AH_TRUE;
	pCap->hal4AddrAggrSupport = AH_FALSE;	/* Broken in Owl */
	pCap->halSpectralScanSupport = AH_FALSE;	/* AR9280 and later */

	if (ath_hal_eepromGet(ah, AR_EEP_MAXQCU, &val) == HAL_OK)
		pCap->halTotalQueues = val;
	else
		pCap->halTotalQueues = HAL_NUM_TX_QUEUES;

	if (ath_hal_eepromGet(ah, AR_EEP_KCENTRIES, &val) == HAL_OK)
		pCap->halKeyCacheSize = val;
	else
		pCap->halKeyCacheSize = AR5416_KEYTABLE_SIZE;

	/* XXX Which chips? */
	pCap->halChanHalfRate = AH_TRUE;
	pCap->halChanQuarterRate = AH_TRUE;

	pCap->halTxTstampPrecision = 32;
	pCap->halRxTstampPrecision = 32;
	pCap->halHwPhyCounterSupport = AH_TRUE;
	pCap->halIntrMask = HAL_INT_COMMON
			| HAL_INT_RX
			| HAL_INT_TX
			| HAL_INT_FATAL
			| HAL_INT_BNR
			| HAL_INT_BMISC
			| HAL_INT_DTIMSYNC
			| HAL_INT_TSFOOR
			| HAL_INT_CST
			| HAL_INT_GTT
			;

	pCap->halFastCCSupport = AH_TRUE;
	pCap->halNumGpioPins = 14;
	pCap->halWowSupport = AH_FALSE;
	pCap->halWowMatchPatternExact = AH_FALSE;
	pCap->halBtCoexSupport = AH_FALSE;	/* XXX need support */
	pCap->halAutoSleepSupport = AH_FALSE;
	pCap->hal4kbSplitTransSupport = AH_TRUE;
	/* Disable this so Block-ACK works correctly */
	pCap->halHasRxSelfLinkedTail = AH_FALSE;
#if 0	/* XXX not yet */
	pCap->halNumAntCfg2GHz = ar5416GetNumAntConfig(ahp, HAL_FREQ_BAND_2GHZ);
	pCap->halNumAntCfg5GHz = ar5416GetNumAntConfig(ahp, HAL_FREQ_BAND_5GHZ);
#endif
	pCap->halHTSupport = AH_TRUE;
	pCap->halTxChainMask = ath_hal_eepromGet(ah, AR_EEP_TXMASK, AH_NULL);
	/* XXX CB71 uses GPIO 0 to indicate 3 rx chains */
	pCap->halRxChainMask = ath_hal_eepromGet(ah, AR_EEP_RXMASK, AH_NULL);
	/* AR5416 may have 3 antennas but is a 2x2 stream device */
	pCap->halTxStreams = 2;
	pCap->halRxStreams = 2;

	/*
	 * If the TX or RX chainmask has less than 2 chains active,
	 * mark it as a 1-stream device for the relevant stream.
	 */
	if (owl_get_ntxchains(pCap->halTxChainMask) == 1)
		pCap->halTxStreams = 1;
	/* XXX Eww */
	if (owl_get_ntxchains(pCap->halRxChainMask) == 1)
		pCap->halRxStreams = 1;
	pCap->halRtsAggrLimit = 8*1024;		/* Owl 2.0 limit */
	pCap->halMbssidAggrSupport = AH_FALSE;	/* Broken on Owl */
	pCap->halForcePpmSupport = AH_TRUE;
	pCap->halEnhancedPmSupport = AH_TRUE;
	pCap->halBssidMatchSupport = AH_TRUE;
	pCap->halGTTSupport = AH_TRUE;
	pCap->halCSTSupport = AH_TRUE;
	pCap->halEnhancedDfsSupport = AH_FALSE;
	/*
	 * BB Read WAR: this is only for AR5008/AR9001 NICs
	 * It is also set individually in the AR91xx attach functions.
	 */
	if (AR_SREV_OWL(ah))
		pCap->halHasBBReadWar = AH_TRUE;

	if (ath_hal_eepromGetFlag(ah, AR_EEP_RFKILL) &&
	    ath_hal_eepromGet(ah, AR_EEP_RFSILENT, &ahpriv->ah_rfsilent) == HAL_OK) {
		/* NB: enabled by default */
		ahpriv->ah_rfkillEnabled = AH_TRUE;
		pCap->halRfSilentSupport = AH_TRUE;
	}

	/*
	 * The MAC will mark frames as RXed if there's a descriptor
	 * to write them to. So if it hits a self-linked final descriptor,
	 * it'll keep ACKing frames even though they're being silently
	 * dropped. Thus, this particular feature of the driver can't
	 * be used for 802.11n devices.
	 */
	ahpriv->ah_rxornIsFatal = AH_FALSE;

	/*
	 * If it's a PCI NIC, ask the HAL OS layer to serialise
	 * register access, or SMP machines may cause the hardware
	 * to hang. This is applicable to AR5416 and AR9220; I'm not
	 * sure about AR9160 or AR9227.
	 */
	if (! AH_PRIVATE(ah)->ah_ispcie)
		pCap->halSerialiseRegWar = 1;

	/*
	 * AR5416 and later NICs support MYBEACON filtering.
	 */
	pCap->halRxDoMyBeacon = AH_TRUE;

	return AH_TRUE;
}