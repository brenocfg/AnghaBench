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
typedef  int u_int32_t ;
struct ath_hal_5416 {int ah_btCoexFlag; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int ath_hal_desc_tpc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah_extra_txpow; int /*<<< orphan*/  ah_power_limit; TYPE_1__ ah_config; } ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_TPC ; 
#define  HAL_BT_COEX_ANTENNA_DIVERSITY 130 
 int HAL_BT_COEX_FLAG_LOWER_TX_PWR ; 
 int HAL_BT_COEX_FLAG_LOW_ACK_PWR ; 
 int /*<<< orphan*/  HAL_BT_COEX_HIGH_ACK_POWER ; 
#define  HAL_BT_COEX_LOWER_TX_PWR 129 
 int /*<<< orphan*/  HAL_BT_COEX_LOW_ACK_POWER ; 
#define  HAL_BT_COEX_SET_ACK_PWR 128 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5416SetTxPowerLimit (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5416BTCoexSetParameter(struct ath_hal *ah, u_int32_t type, u_int32_t value)
{
	struct ath_hal_5416 *ahp = AH5416(ah);

	switch (type) {
	case HAL_BT_COEX_SET_ACK_PWR:
		if (value) {
			ahp->ah_btCoexFlag |= HAL_BT_COEX_FLAG_LOW_ACK_PWR;
			OS_REG_WRITE(ah, AR_TPC, HAL_BT_COEX_LOW_ACK_POWER);
		} else {
			ahp->ah_btCoexFlag &= ~HAL_BT_COEX_FLAG_LOW_ACK_PWR;
			OS_REG_WRITE(ah, AR_TPC, HAL_BT_COEX_HIGH_ACK_POWER);
		}
		break;
	case HAL_BT_COEX_ANTENNA_DIVERSITY:
		/* This is overridden for Kite */
		break;
#if 0
        case HAL_BT_COEX_LOWER_TX_PWR:
            if (value) {
                if ((ahp->ah_btCoexFlag & HAL_BT_COEX_FLAG_LOWER_TX_PWR) == 0) {
                    ahp->ah_btCoexFlag |= HAL_BT_COEX_FLAG_LOWER_TX_PWR;
		    AH_PRIVATE(ah)->ah_config.ath_hal_desc_tpc = 1;
                    ar5416SetTxPowerLimit(ah, AH_PRIVATE(ah)->ah_power_limit, AH_PRIVATE(ah)->ah_extra_txpow, 0);
                }
            }
            else {
                if (ahp->ah_btCoexFlag & HAL_BT_COEX_FLAG_LOWER_TX_PWR) {
                    ahp->ah_btCoexFlag &= ~HAL_BT_COEX_FLAG_LOWER_TX_PWR;
		    AH_PRIVATE(ah)->ah_config.ath_hal_desc_tpc = 0;
                    ar5416SetTxPowerLimit(ah, AH_PRIVATE(ah)->ah_power_limit, AH_PRIVATE(ah)->ah_extra_txpow, 0);
                }
            }
            break;
#endif
	default:
			break;
	}
}