#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_7__ {int version; scalar_t__ txGainType; } ;
struct TYPE_8__ {int antCtrlCommon; int version; scalar_t__ ob_0; scalar_t__ ob_1; scalar_t__ ob_2; scalar_t__ ob_3; scalar_t__ ob_4; scalar_t__ db1_0; scalar_t__ db1_1; scalar_t__ db1_2; scalar_t__ db1_3; scalar_t__ db1_4; scalar_t__ db2_0; scalar_t__ db2_1; scalar_t__ db2_2; scalar_t__ db2_3; scalar_t__ db2_4; scalar_t__ bb_scale_smrt_antenna; int /*<<< orphan*/  swSettleHt40; int /*<<< orphan*/  txFrameToPaOn; int /*<<< orphan*/  txFrameToDataStart; int /*<<< orphan*/  thresh62; int /*<<< orphan*/  txEndToRxOn; int /*<<< orphan*/  txFrameToXpaOn; int /*<<< orphan*/  txEndToXpaOff; int /*<<< orphan*/  adcDesiredSize; int /*<<< orphan*/  switchSettling; } ;
struct ar5416eeprom_4k {TYPE_1__ baseEepHeader; TYPE_2__ modalHeader; } ;
struct TYPE_11__ {int /*<<< orphan*/  ah_antControl; } ;
struct TYPE_10__ {TYPE_3__* ah_eeprom; } ;
struct TYPE_9__ {struct ar5416eeprom_4k ee_base; } ;
typedef  TYPE_2__ MODAL_EEP4K_HEADER ;
typedef  TYPE_3__ HAL_EEPROM_v4k ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_6__* AH5212 (struct ath_hal*) ; 
 TYPE_5__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR5416_EEP_MINOR_VER_2 ; 
 int AR5416_EEP_MINOR_VER_3 ; 
 int AR5416_EEP_VER_MINOR_MASK ; 
 int /*<<< orphan*/  AR9280_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_DB1_0 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_DB1_1 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_DB1_2 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_OB_0 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_OB_1 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_OB_2 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_OB_3 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G3_OB_4 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB1_3 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB1_4 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB2_0 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB2_1 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB2_2 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB2_3 ; 
 int /*<<< orphan*/  AR9285_AN_RF2G4_DB2_4 ; 
 int /*<<< orphan*/  AR_PHY_CCA ; 
 int /*<<< orphan*/  AR_PHY_CH0_TX_PWRCTRL11 ; 
 int /*<<< orphan*/  AR_PHY_CH0_TX_PWRCTRL12 ; 
 int /*<<< orphan*/  AR_PHY_CH0_TX_PWRCTRL13 ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ_ADC ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL2 ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL3 ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL4 ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL4_FRAME_XPAA_ON ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL4_FRAME_XPAB_ON ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL4_TX_END_XPAA_OFF ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL4_TX_END_XPAB_OFF ; 
 int /*<<< orphan*/  AR_PHY_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_SETTLING_SWITCH ; 
 int /*<<< orphan*/  AR_PHY_SWITCH_COM ; 
 int /*<<< orphan*/  AR_PHY_TX_END_TO_A2_RX_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_FRAME_TO_DATA_START ; 
 int /*<<< orphan*/  AR_PHY_TX_FRAME_TO_PA_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL10 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL8 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL9 ; 
 scalar_t__ AR_SREV_9271 (struct ath_hal*) ; 
 scalar_t__ AR_SREV_KITE (struct ath_hal*) ; 
 scalar_t__ EEP_4K_BB_DESIRED_SCALE_MASK ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_A_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9285SetAntennaSwitch (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9285SetBoardGain (struct ath_hal*,TYPE_2__ const*,struct ar5416eeprom_4k const*,scalar_t__) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*) ; 

HAL_BOOL
ar9285SetBoardValues(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	const HAL_EEPROM_v4k *ee = AH_PRIVATE(ah)->ah_eeprom;
	const struct ar5416eeprom_4k *eep = &ee->ee_base;
	const MODAL_EEP4K_HEADER *pModal;
	uint8_t txRxAttenLocal;
	uint8_t ob[5], db1[5], db2[5];

	pModal = &eep->modalHeader;
	txRxAttenLocal = 23;

	OS_REG_WRITE(ah, AR_PHY_SWITCH_COM, pModal->antCtrlCommon);

	/* Single chain for 4K EEPROM*/
	ar9285SetBoardGain(ah, pModal, eep, txRxAttenLocal);

	/* Initialize Ant Diversity settings if supported */
	(void) ar9285SetAntennaSwitch(ah, AH5212(ah)->ah_antControl);

	/* Configure TX power calibration */
	if (pModal->version >= 2) {
		ob[0] = pModal->ob_0;
		ob[1] = pModal->ob_1;
		ob[2] = pModal->ob_2;
		ob[3] = pModal->ob_3;
		ob[4] = pModal->ob_4;

		db1[0] = pModal->db1_0;
		db1[1] = pModal->db1_1;
		db1[2] = pModal->db1_2;
		db1[3] = pModal->db1_3;
		db1[4] = pModal->db1_4;

		db2[0] = pModal->db2_0;
		db2[1] = pModal->db2_1;
		db2[2] = pModal->db2_2;
		db2[3] = pModal->db2_3;
		db2[4] = pModal->db2_4;
	} else if (pModal->version == 1) {
		ob[0] = pModal->ob_0;
		ob[1] = ob[2] = ob[3] = ob[4] = pModal->ob_1;
		db1[0] = pModal->db1_0;
		db1[1] = db1[2] = db1[3] = db1[4] = pModal->db1_1;
		db2[0] = pModal->db2_0;
		db2[1] = db2[2] = db2[3] = db2[4] = pModal->db2_1;
	} else {
		int i;

		for (i = 0; i < 5; i++) {
			ob[i] = pModal->ob_0;
			db1[i] = pModal->db1_0;
			db2[i] = pModal->db1_0;
		}
	}

	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_OB_0, ob[0]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_OB_1, ob[1]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_OB_2, ob[2]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_OB_3, ob[3]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_OB_4, ob[4]);

	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_DB1_0, db1[0]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_DB1_1, db1[1]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_DB1_2, db1[2]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB1_3, db1[3]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB1_4, db1[4]);

	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB2_0, db2[0]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB2_1, db2[1]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB2_2, db2[2]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB2_3, db2[3]);
	OS_A_REG_RMW_FIELD(ah, AR9285_AN_RF2G4, AR9285_AN_RF2G4_DB2_4, db2[4]);

	OS_REG_RMW_FIELD(ah, AR_PHY_SETTLING, AR_PHY_SETTLING_SWITCH,
		      pModal->switchSettling);
	OS_REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ, AR_PHY_DESIRED_SZ_ADC,
		      pModal->adcDesiredSize);

	OS_REG_WRITE(ah, AR_PHY_RF_CTL4,
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAA_OFF) |
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAB_OFF) |
		  SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAA_ON)  |
		  SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAB_ON));

	OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL3, AR_PHY_TX_END_TO_A2_RX_ON,
		      pModal->txEndToRxOn);

	OS_REG_RMW_FIELD(ah, AR_PHY_CCA, AR9280_PHY_CCA_THRESH62,
		      pModal->thresh62);
	OS_REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0, AR_PHY_EXT_CCA0_THRESH62,
		      pModal->thresh62);

	if ((eep->baseEepHeader.version & AR5416_EEP_VER_MINOR_MASK) >=
	    AR5416_EEP_MINOR_VER_2) {
		OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL2, AR_PHY_TX_FRAME_TO_DATA_START,
		    pModal->txFrameToDataStart);
		OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL2, AR_PHY_TX_FRAME_TO_PA_ON,
		    pModal->txFrameToPaOn);
	}

	if ((eep->baseEepHeader.version & AR5416_EEP_VER_MINOR_MASK) >=
	    AR5416_EEP_MINOR_VER_3) {
		if (IEEE80211_IS_CHAN_HT40(chan))
			OS_REG_RMW_FIELD(ah, AR_PHY_SETTLING,
			    AR_PHY_SETTLING_SWITCH, pModal->swSettleHt40);
	}

	/*
	 * Program the CCK TX gain factor appropriately if needed.
	 * The AR9285/AR9271 has a non-constant PA tx gain behaviour
	 * for CCK versus OFDM rates; other chips deal with this
	 * differently.
	 *
	 * The mask/shift/multiply hackery is done so place the same
	 * value (bb_desired_scale) into multiple 5-bit fields.
	 * For example, AR_PHY_TX_PWRCTRL9 has bb_desired_scale written
	 * to three fields: (0..4), (5..9) and (10..14).
	 */
	if (AR_SREV_9271(ah) || AR_SREV_KITE(ah)) {
		uint8_t bb_desired_scale = (pModal->bb_scale_smrt_antenna & EEP_4K_BB_DESIRED_SCALE_MASK);
		if ((eep->baseEepHeader.txGainType == 0) && (bb_desired_scale != 0)) {
			ath_hal_printf(ah, "[ath]: adjusting cck tx gain factor\n");
			uint32_t pwrctrl, mask, clr;

			mask = (1<<0) | (1<<5) | (1<<10) | (1<<15) | (1<<20) | (1<<25);
			pwrctrl = mask * bb_desired_scale;
			clr = mask * 0x1f;
			OS_REG_RMW(ah, AR_PHY_TX_PWRCTRL8, pwrctrl, clr);
			OS_REG_RMW(ah, AR_PHY_TX_PWRCTRL10, pwrctrl, clr);
			OS_REG_RMW(ah, AR_PHY_CH0_TX_PWRCTRL12, pwrctrl, clr);

			mask = (1<<0) | (1<<5) | (1<<15);
			pwrctrl = mask * bb_desired_scale;
			clr = mask * 0x1f;
			OS_REG_RMW(ah, AR_PHY_TX_PWRCTRL9, pwrctrl, clr);

			mask = (1<<0) | (1<<5);
			pwrctrl = mask * bb_desired_scale;
			clr = mask * 0x1f;
			OS_REG_RMW(ah, AR_PHY_CH0_TX_PWRCTRL11, pwrctrl, clr);
			OS_REG_RMW(ah, AR_PHY_CH0_TX_PWRCTRL13, pwrctrl, clr);
		}
	}

	return AH_TRUE;
}