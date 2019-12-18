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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ pe_firpwr; scalar_t__ pe_rrssi; scalar_t__ pe_height; scalar_t__ pe_prssi; scalar_t__ pe_inband; int pe_enabled; int pe_usefir128; int pe_enmaxrssi; int pe_blockradar; scalar_t__ pe_relstep; scalar_t__ pe_relpwr; int pe_en_relstep_check; int pe_enrelpwr; scalar_t__ pe_maxlen; int pe_extchannel; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_ENA ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FFT_ENA ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FIRPWR ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_HEIGHT ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_INBAND ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_PRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_RRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_BLOCK_CHECK ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_MAXLEN ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_MAX_RRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELPWR_ENA ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELPWR_THRESH ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELSTEP_CHECK ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELSTEP_THRESH ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_USE_FIR128 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_EXT ; 
 int /*<<< orphan*/  AR_PHY_RADAR_EXT_ENA ; 
 scalar_t__ HAL_PHYERR_PARAM_NOVAL ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM (scalar_t__,int /*<<< orphan*/ ) ; 

void
ar5416EnableDfs(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{
	uint32_t val;

	val = OS_REG_READ(ah, AR_PHY_RADAR_0);

	if (pe->pe_firpwr != HAL_PHYERR_PARAM_NOVAL) {
		val &= ~AR_PHY_RADAR_0_FIRPWR;
		val |= SM(pe->pe_firpwr, AR_PHY_RADAR_0_FIRPWR);
	}
	if (pe->pe_rrssi != HAL_PHYERR_PARAM_NOVAL) {
		val &= ~AR_PHY_RADAR_0_RRSSI;
		val |= SM(pe->pe_rrssi, AR_PHY_RADAR_0_RRSSI);
	}
	if (pe->pe_height != HAL_PHYERR_PARAM_NOVAL) {
		val &= ~AR_PHY_RADAR_0_HEIGHT;
		val |= SM(pe->pe_height, AR_PHY_RADAR_0_HEIGHT);
	}
	if (pe->pe_prssi != HAL_PHYERR_PARAM_NOVAL) {
		val &= ~AR_PHY_RADAR_0_PRSSI;
		val |= SM(pe->pe_prssi, AR_PHY_RADAR_0_PRSSI);
	}
	if (pe->pe_inband != HAL_PHYERR_PARAM_NOVAL) {
		val &= ~AR_PHY_RADAR_0_INBAND;
		val |= SM(pe->pe_inband, AR_PHY_RADAR_0_INBAND);
	}

	/*Enable FFT data*/
	val |= AR_PHY_RADAR_0_FFT_ENA;
	OS_REG_WRITE(ah, AR_PHY_RADAR_0, val);

	/* Implicitly enable */
	if (pe->pe_enabled == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_ENA);
	else if (pe->pe_enabled == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_ENA);

	if (pe->pe_usefir128 == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_USE_FIR128);
	else if (pe->pe_usefir128 == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_USE_FIR128);

	if (pe->pe_enmaxrssi == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_MAX_RRSSI);
	else if (pe->pe_enmaxrssi == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_MAX_RRSSI);

	if (pe->pe_blockradar == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_BLOCK_CHECK);
	else if (pe->pe_blockradar == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_1, AR_PHY_RADAR_1_BLOCK_CHECK);

	if (pe->pe_relstep != HAL_PHYERR_PARAM_NOVAL) {
		val = OS_REG_READ(ah, AR_PHY_RADAR_1);
		val &= ~AR_PHY_RADAR_1_RELSTEP_THRESH;
		val |= SM(pe->pe_relstep, AR_PHY_RADAR_1_RELSTEP_THRESH);
		OS_REG_WRITE(ah, AR_PHY_RADAR_1, val);
	}
	if (pe->pe_relpwr != HAL_PHYERR_PARAM_NOVAL) {
		val = OS_REG_READ(ah, AR_PHY_RADAR_1);
		val &= ~AR_PHY_RADAR_1_RELPWR_THRESH;
		val |= SM(pe->pe_relpwr, AR_PHY_RADAR_1_RELPWR_THRESH);
		OS_REG_WRITE(ah, AR_PHY_RADAR_1, val);
	}

	if (pe->pe_en_relstep_check == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_1,
		    AR_PHY_RADAR_1_RELSTEP_CHECK);
	else if (pe->pe_en_relstep_check == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_1,
		    AR_PHY_RADAR_1_RELSTEP_CHECK);

	if (pe->pe_enrelpwr == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_1,
		    AR_PHY_RADAR_1_RELPWR_ENA);
	else if (pe->pe_enrelpwr == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_1,
		    AR_PHY_RADAR_1_RELPWR_ENA);

	if (pe->pe_maxlen != HAL_PHYERR_PARAM_NOVAL) {
		val = OS_REG_READ(ah, AR_PHY_RADAR_1);
		val &= ~AR_PHY_RADAR_1_MAXLEN;
		val |= SM(pe->pe_maxlen, AR_PHY_RADAR_1_MAXLEN);
		OS_REG_WRITE(ah, AR_PHY_RADAR_1, val);
	}

	/*
	 * Enable HT/40 if the upper layer asks;
	 * it should check the channel is HT/40 and HAL_CAP_EXT_CHAN_DFS
	 * is available.
	 */
	if (pe->pe_extchannel == 1)
		OS_REG_SET_BIT(ah, AR_PHY_RADAR_EXT, AR_PHY_RADAR_EXT_ENA);
	else if (pe->pe_extchannel == 0)
		OS_REG_CLR_BIT(ah, AR_PHY_RADAR_EXT, AR_PHY_RADAR_EXT_ENA);
}