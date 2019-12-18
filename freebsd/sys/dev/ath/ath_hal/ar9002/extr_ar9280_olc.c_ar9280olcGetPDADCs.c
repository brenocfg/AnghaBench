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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 size_t AR5416_NUM_PDADC_VALUES ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL6_0 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL6_1 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL7 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_ERR_EST_MODE ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_INIT_TX_GAIN ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void
ar9280olcGetPDADCs(struct ath_hal *ah, uint32_t initTxGain, int txPower,
    uint8_t *pPDADCValues)
{
	uint32_t i;
	uint32_t offset;

	OS_REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL6_0, AR_PHY_TX_PWRCTRL_ERR_EST_MODE, 3);
	OS_REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL6_1, AR_PHY_TX_PWRCTRL_ERR_EST_MODE, 3);

	OS_REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL7, AR_PHY_TX_PWRCTRL_INIT_TX_GAIN, initTxGain);

	offset = txPower;
	for (i = 0; i < AR5416_NUM_PDADC_VALUES; i++)
		if (i < offset)
			pPDADCValues[i] = 0x0;
		else
			pPDADCValues[i] = 0xFF;
}