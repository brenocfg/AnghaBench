#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ath_hal {int dummy; } ;
struct ar5416eeprom {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rxTxMarginCh; int /*<<< orphan*/ * bswAtten; int /*<<< orphan*/ * bswMargin; int /*<<< orphan*/ * xatten2Db; int /*<<< orphan*/ * xatten2Margin; int /*<<< orphan*/ * txRxAttenCh; } ;
typedef  TYPE_1__ MODAL_EEP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_ATTEN ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_MARGIN ; 
 scalar_t__ AR_PHY_GAIN_2GHZ ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_BSW_ATTEN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_BSW_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_RXTX_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN ; 
 scalar_t__ AR_PHY_RXGAIN ; 
 int /*<<< orphan*/  AR_PHY_RXGAIN_TXRX_ATTEN ; 
 scalar_t__ AR_SREV_MERLIN_10_OR_LATER (struct ath_hal*) ; 
 scalar_t__ IS_EEP_MINOR_V3 (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5416SetDefGainValues(struct ath_hal *ah,
    const MODAL_EEP_HEADER *pModal,
    const struct ar5416eeprom *eep,
    uint8_t txRxAttenLocal, int regChainOffset, int i)
{

	if (IS_EEP_MINOR_V3(ah)) {
		txRxAttenLocal = pModal->txRxAttenCh[i];

		if (AR_SREV_MERLIN_10_OR_LATER(ah)) {
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[i]);
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[i]);
		} else {
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_BSW_MARGIN,
			      pModal->bswMargin[i]);
			OS_REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_BSW_ATTEN,
			      pModal->bswAtten[i]);
		}
	}

	if (AR_SREV_MERLIN_10_OR_LATER(ah)) {
		OS_REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
		OS_REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[i]);
	} else {
		OS_REG_RMW_FIELD(ah,
			  AR_PHY_RXGAIN + regChainOffset,
			  AR_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
		OS_REG_RMW_FIELD(ah,
			  AR_PHY_GAIN_2GHZ + regChainOffset,
			  AR_PHY_GAIN_2GHZ_RXTX_MARGIN, pModal->rxTxMarginCh[i]);
	}
}