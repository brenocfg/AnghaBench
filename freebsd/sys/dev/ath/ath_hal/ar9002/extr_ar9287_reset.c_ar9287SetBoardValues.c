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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct modal_eep_ar9287_header {int antCtrlCommon; int* antCtrlChain; int /*<<< orphan*/  xpaBiasLvl; int /*<<< orphan*/  txFrameToPaOn; int /*<<< orphan*/  txFrameToDataStart; int /*<<< orphan*/  ob_pal_off; int /*<<< orphan*/  ob_qam; int /*<<< orphan*/  ob_psk; int /*<<< orphan*/  ob_cck; int /*<<< orphan*/  db2; int /*<<< orphan*/  db1; int /*<<< orphan*/  thresh62; int /*<<< orphan*/  txEndToRxOn; int /*<<< orphan*/  txFrameToXpaOn; int /*<<< orphan*/  txEndToXpaOff; int /*<<< orphan*/  adcDesiredSize; int /*<<< orphan*/  switchSettling; int /*<<< orphan*/  swSettleHt40; int /*<<< orphan*/ * rxTxMarginCh; int /*<<< orphan*/ * bswAtten; int /*<<< orphan*/ * bswMargin; int /*<<< orphan*/ * txRxAttenCh; int /*<<< orphan*/ * iqCalQCh; int /*<<< orphan*/ * iqCalICh; } ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct ar9287_eeprom {struct modal_eep_ar9287_header modalHeader; } ;
struct TYPE_4__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_3__ {struct ar9287_eeprom ee_base; } ;
typedef  TYPE_1__ HAL_EEPROM_9287 ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR9280_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_ATTEN ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_MARGIN ; 
 int AR9287_ANT_16S ; 
 scalar_t__ AR9287_AN_RF2G3_CH0 ; 
 scalar_t__ AR9287_AN_RF2G3_CH1 ; 
 int AR9287_AN_RF2G3_DB1 ; 
 int AR9287_AN_RF2G3_DB2 ; 
 int AR9287_AN_RF2G3_OB_CCK ; 
 int AR9287_AN_RF2G3_OB_PAL_OFF ; 
 int AR9287_AN_RF2G3_OB_PSK ; 
 int AR9287_AN_RF2G3_OB_QAM ; 
 int /*<<< orphan*/  AR9287_AN_TOP2 ; 
 int /*<<< orphan*/  AR9287_AN_TOP2_XPABIAS_LVL ; 
 int AR9287_MAX_CHAINS ; 
 scalar_t__ AR_PHY_CCA ; 
 scalar_t__ AR_PHY_DESIRED_SZ ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ_ADC ; 
 scalar_t__ AR_PHY_EXT_CCA0 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0_THRESH62 ; 
 scalar_t__ AR_PHY_GAIN_2GHZ ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN ; 
 scalar_t__ AR_PHY_RF_CTL2 ; 
 scalar_t__ AR_PHY_RF_CTL3 ; 
 scalar_t__ AR_PHY_RF_CTL4 ; 
 int AR_PHY_RF_CTL4_FRAME_XPAA_ON ; 
 int AR_PHY_RF_CTL4_FRAME_XPAB_ON ; 
 int AR_PHY_RF_CTL4_TX_END_XPAA_OFF ; 
 int AR_PHY_RF_CTL4_TX_END_XPAB_OFF ; 
 scalar_t__ AR_PHY_RXGAIN ; 
 scalar_t__ AR_PHY_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_SETTLING_SWITCH ; 
 scalar_t__ AR_PHY_SWITCH_CHAIN_0 ; 
 scalar_t__ AR_PHY_SWITCH_COM ; 
 scalar_t__ AR_PHY_TIMING_CTRL4_CHAIN (int /*<<< orphan*/ ) ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF ; 
 int /*<<< orphan*/  AR_PHY_TX_END_TO_A2_RX_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_FRAME_TO_DATA_START ; 
 int /*<<< orphan*/  AR_PHY_TX_FRAME_TO_PA_ON ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_A_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_A_REG_WRITE (struct ath_hal*,scalar_t__,int) ; 
 int OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,scalar_t__,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 

HAL_BOOL
ar9287SetBoardValues(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	const HAL_EEPROM_9287 *ee = AH_PRIVATE(ah)->ah_eeprom;
	const struct ar9287_eeprom *eep = &ee->ee_base;
	const struct modal_eep_ar9287_header *pModal = &eep->modalHeader;
	uint16_t antWrites[AR9287_ANT_16S];
	uint32_t regChainOffset, regval;
	uint8_t txRxAttenLocal;
	int i, j, offset_num;

	pModal = &eep->modalHeader;

	antWrites[0] = (uint16_t)((pModal->antCtrlCommon >> 28) & 0xF);
	antWrites[1] = (uint16_t)((pModal->antCtrlCommon >> 24) & 0xF);
	antWrites[2] = (uint16_t)((pModal->antCtrlCommon >> 20) & 0xF);
	antWrites[3] = (uint16_t)((pModal->antCtrlCommon >> 16) & 0xF);
	antWrites[4] = (uint16_t)((pModal->antCtrlCommon >> 12) & 0xF);
	antWrites[5] = (uint16_t)((pModal->antCtrlCommon >> 8) & 0xF);
	antWrites[6] = (uint16_t)((pModal->antCtrlCommon >> 4)  & 0xF);
	antWrites[7] = (uint16_t)(pModal->antCtrlCommon & 0xF);

	offset_num = 8;

	for (i = 0, j = offset_num; i < AR9287_MAX_CHAINS; i++) {
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 28) & 0xf);
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 10) & 0x3);
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 8) & 0x3);
		antWrites[j++] = 0;
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 6) & 0x3);
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 4) & 0x3);
		antWrites[j++] = (uint16_t)((pModal->antCtrlChain[i] >> 2) & 0x3);
		antWrites[j++] = (uint16_t)(pModal->antCtrlChain[i] & 0x3);
	}

	OS_REG_WRITE(ah, AR_PHY_SWITCH_COM, pModal->antCtrlCommon);

	for (i = 0; i < AR9287_MAX_CHAINS; i++)	{
		regChainOffset = i * 0x1000;

		OS_REG_WRITE(ah, AR_PHY_SWITCH_CHAIN_0 + regChainOffset,
			  pModal->antCtrlChain[i]);

		OS_REG_WRITE(ah, AR_PHY_TIMING_CTRL4_CHAIN(0) + regChainOffset,
			  (OS_REG_READ(ah, AR_PHY_TIMING_CTRL4_CHAIN(0)
			      + regChainOffset)
			   & ~(AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF |
			       AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF)) |
			  SM(pModal->iqCalICh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
			  SM(pModal->iqCalQCh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF));

		txRxAttenLocal = pModal->txRxAttenCh[i];

		OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
		OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
		OS_REG_RMW_FIELD(ah, AR_PHY_RXGAIN + regChainOffset,
			      AR9280_PHY_RXGAIN_TXRX_ATTEN,
			      txRxAttenLocal);
		OS_REG_RMW_FIELD(ah, AR_PHY_RXGAIN + regChainOffset,
			      AR9280_PHY_RXGAIN_TXRX_MARGIN,
			      pModal->rxTxMarginCh[i]);
	}

	if (IEEE80211_IS_CHAN_HT40(chan))
		OS_REG_RMW_FIELD(ah, AR_PHY_SETTLING,
			      AR_PHY_SETTLING_SWITCH, pModal->swSettleHt40);
	else
		OS_REG_RMW_FIELD(ah, AR_PHY_SETTLING,
			      AR_PHY_SETTLING_SWITCH, pModal->switchSettling);

	OS_REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ,
		      AR_PHY_DESIRED_SZ_ADC, pModal->adcDesiredSize);

	OS_REG_WRITE(ah, AR_PHY_RF_CTL4,
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAA_OFF)
		  | SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAB_OFF)
		  | SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAA_ON)
		  | SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAB_ON));

	OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL3,
		      AR_PHY_TX_END_TO_A2_RX_ON, pModal->txEndToRxOn);

	OS_REG_RMW_FIELD(ah, AR_PHY_CCA,
		      AR9280_PHY_CCA_THRESH62, pModal->thresh62);
	OS_REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0,
		      AR_PHY_EXT_CCA0_THRESH62, pModal->thresh62);

	regval = OS_REG_READ(ah, AR9287_AN_RF2G3_CH0);
	regval &= ~(AR9287_AN_RF2G3_DB1 |
		    AR9287_AN_RF2G3_DB2 |
		    AR9287_AN_RF2G3_OB_CCK |
		    AR9287_AN_RF2G3_OB_PSK |
		    AR9287_AN_RF2G3_OB_QAM |
		    AR9287_AN_RF2G3_OB_PAL_OFF);
	regval |= (SM(pModal->db1, AR9287_AN_RF2G3_DB1) |
		   SM(pModal->db2, AR9287_AN_RF2G3_DB2) |
		   SM(pModal->ob_cck, AR9287_AN_RF2G3_OB_CCK) |
		   SM(pModal->ob_psk, AR9287_AN_RF2G3_OB_PSK) |
		   SM(pModal->ob_qam, AR9287_AN_RF2G3_OB_QAM) |
		   SM(pModal->ob_pal_off, AR9287_AN_RF2G3_OB_PAL_OFF));

	/* Analog write - requires a 100usec delay */
	OS_A_REG_WRITE(ah, AR9287_AN_RF2G3_CH0, regval);

	regval = OS_REG_READ(ah, AR9287_AN_RF2G3_CH1);
	regval &= ~(AR9287_AN_RF2G3_DB1 |
		    AR9287_AN_RF2G3_DB2 |
		    AR9287_AN_RF2G3_OB_CCK |
		    AR9287_AN_RF2G3_OB_PSK |
		    AR9287_AN_RF2G3_OB_QAM |
		    AR9287_AN_RF2G3_OB_PAL_OFF);
	regval |= (SM(pModal->db1, AR9287_AN_RF2G3_DB1) |
		   SM(pModal->db2, AR9287_AN_RF2G3_DB2) |
		   SM(pModal->ob_cck, AR9287_AN_RF2G3_OB_CCK) |
		   SM(pModal->ob_psk, AR9287_AN_RF2G3_OB_PSK) |
		   SM(pModal->ob_qam, AR9287_AN_RF2G3_OB_QAM) |
		   SM(pModal->ob_pal_off, AR9287_AN_RF2G3_OB_PAL_OFF));

	OS_A_REG_WRITE(ah, AR9287_AN_RF2G3_CH1, regval);

	OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
	    AR_PHY_TX_FRAME_TO_DATA_START, pModal->txFrameToDataStart);
	OS_REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
	    AR_PHY_TX_FRAME_TO_PA_ON, pModal->txFrameToPaOn);

	OS_A_REG_RMW_FIELD(ah, AR9287_AN_TOP2,
	    AR9287_AN_TOP2_XPABIAS_LVL, pModal->xpaBiasLvl);

	return AH_TRUE;
}