#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ah_miscMode; } ;
struct TYPE_4__ {int halRxChainMask; int halRxStreams; int halTxChainMask; int halTxStreams; } ;
struct TYPE_5__ {TYPE_1__ ah_caps; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_3__* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_EEP_RXMASK ; 
 int /*<<< orphan*/  AR_EEP_TXMASK ; 
 int /*<<< orphan*/  AR_MISC_MODE ; 
 int /*<<< orphan*/  AR_PCU_TXOP_TBTT_LIMIT_ENA ; 
#define  HAL_CAP_ENFORCE_TXOP 130 
#define  HAL_CAP_RX_CHAINMASK 129 
#define  HAL_CAP_TX_CHAINMASK 128 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212SetCapability (struct ath_hal*,int,int,int,int /*<<< orphan*/ *) ; 
 int ath_hal_eepromGet (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int owl_get_ntxchains (int) ; 

HAL_BOOL
ar5416SetCapability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
    u_int32_t capability, u_int32_t setting, HAL_STATUS *status)
{
	HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;

	switch (type) {
	case HAL_CAP_RX_CHAINMASK:
		setting &= ath_hal_eepromGet(ah, AR_EEP_RXMASK, NULL);
		pCap->halRxChainMask = setting;
		if (owl_get_ntxchains(setting) > 2)
			pCap->halRxStreams = 2;
		else
			pCap->halRxStreams = 1;
		return AH_TRUE;
	case HAL_CAP_TX_CHAINMASK:
		setting &= ath_hal_eepromGet(ah, AR_EEP_TXMASK, NULL);
		pCap->halTxChainMask = setting;
		if (owl_get_ntxchains(setting) > 2)
			pCap->halTxStreams = 2;
		else
			pCap->halTxStreams = 1;
		return AH_TRUE;
	case HAL_CAP_ENFORCE_TXOP:
		if (capability != 1)
			return AH_FALSE;
		if (setting) {
			AH5212(ah)->ah_miscMode
			    |= AR_PCU_TXOP_TBTT_LIMIT_ENA;
			OS_REG_SET_BIT(ah, AR_MISC_MODE,
			    AR_PCU_TXOP_TBTT_LIMIT_ENA);
		} else {
			AH5212(ah)->ah_miscMode
			    &= ~AR_PCU_TXOP_TBTT_LIMIT_ENA;
			OS_REG_CLR_BIT(ah, AR_MISC_MODE,
			    AR_PCU_TXOP_TBTT_LIMIT_ENA);
		}
		return AH_TRUE;
	default:
		break;
	}
	return ar5212SetCapability(ah, type, capability, setting, status);
}