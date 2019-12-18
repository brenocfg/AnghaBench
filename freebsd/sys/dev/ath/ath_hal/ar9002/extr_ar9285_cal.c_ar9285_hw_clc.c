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
typedef  int uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 scalar_t__ AH_FALSE ; 
 scalar_t__ AH_TRUE ; 
 int AR9285_CLCAL_REDO_THRESH ; 
 scalar_t__ AR9285_RF2G5 ; 
 int AR9285_RF2G5_IC50TX ; 
 int AR9285_RF2G5_IC50TX_SET ; 
 int AR9285_RF2G5_IC50TX_XE_SET ; 
 int AR_PHY_CLC_I0 ; 
 int AR_PHY_CLC_I0_S ; 
 int AR_PHY_CLC_Q0 ; 
 int AR_PHY_CLC_Q0_S ; 
 scalar_t__ AR_PHY_CLC_TBL1 ; 
 int AR_PHY_TX_GAIN_CLC ; 
 int AR_PHY_TX_GAIN_CLC_S ; 
 scalar_t__ AR_PHY_TX_GAIN_TBL1 ; 
 scalar_t__ AR_PHY_TX_PWRCTRL7 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX ; 
 scalar_t__ AR_SREV_9285E_20 (struct ath_hal*) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,scalar_t__,int) ; 
 scalar_t__ ar9285_hw_cl_cal (struct ath_hal*,struct ieee80211_channel const*) ; 

__attribute__((used)) static HAL_BOOL
ar9285_hw_clc(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	int i;
	uint32_t txgain_max;
	uint32_t clc_gain, gain_mask = 0, clc_num = 0;
	uint32_t reg_clc_I0, reg_clc_Q0;
	uint32_t i0_num = 0;
	uint32_t q0_num = 0;
	uint32_t total_num = 0;
	uint32_t reg_rf2g5_org;
	HAL_BOOL retv = AH_TRUE;

	if (!(ar9285_hw_cl_cal(ah, chan)))
		return AH_FALSE;

	txgain_max = MS(OS_REG_READ(ah, AR_PHY_TX_PWRCTRL7),
			AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX);

	for (i = 0; i < (txgain_max+1); i++) {
		clc_gain = (OS_REG_READ(ah, (AR_PHY_TX_GAIN_TBL1+(i<<2))) &
			   AR_PHY_TX_GAIN_CLC) >> AR_PHY_TX_GAIN_CLC_S;
		if (!(gain_mask & (1 << clc_gain))) {
			gain_mask |= (1 << clc_gain);
			clc_num++;
		}
	}

	for (i = 0; i < clc_num; i++) {
		reg_clc_I0 = (OS_REG_READ(ah, (AR_PHY_CLC_TBL1 + (i << 2)))
			      & AR_PHY_CLC_I0) >> AR_PHY_CLC_I0_S;
		reg_clc_Q0 = (OS_REG_READ(ah, (AR_PHY_CLC_TBL1 + (i << 2)))
			      & AR_PHY_CLC_Q0) >> AR_PHY_CLC_Q0_S;
		if (reg_clc_I0 == 0)
			i0_num++;

		if (reg_clc_Q0 == 0)
			q0_num++;
	}
	total_num = i0_num + q0_num;
	if (total_num > AR9285_CLCAL_REDO_THRESH) {
		reg_rf2g5_org = OS_REG_READ(ah, AR9285_RF2G5);
		if (AR_SREV_9285E_20(ah)) {
			OS_REG_WRITE(ah, AR9285_RF2G5,
				  (reg_rf2g5_org & AR9285_RF2G5_IC50TX) |
				  AR9285_RF2G5_IC50TX_XE_SET);
		} else {
			OS_REG_WRITE(ah, AR9285_RF2G5,
				  (reg_rf2g5_org & AR9285_RF2G5_IC50TX) |
				  AR9285_RF2G5_IC50TX_SET);
		}
		retv = ar9285_hw_cl_cal(ah, chan);
		OS_REG_WRITE(ah, AR9285_RF2G5, reg_rf2g5_org);
	}
	return retv;
}