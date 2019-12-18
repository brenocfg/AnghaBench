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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int pe_firpwr; int pe_extchannel; int pe_usefir128; int pe_blockradar; int pe_enmaxrssi; int pe_enabled; int pe_enrelpwr; int pe_en_relstep_check; void* pe_maxlen; void* pe_relstep; void* pe_relpwr; void* pe_inband; void* pe_prssi; void* pe_height; void* pe_rrssi; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int AR_PHY_RADAR_0_ENA ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FIRPWR ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_HEIGHT ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_INBAND ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_PRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_RRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1 ; 
 int AR_PHY_RADAR_1_BLOCK_CHECK ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_MAXLEN ; 
 int AR_PHY_RADAR_1_MAX_RRSSI ; 
 int AR_PHY_RADAR_1_RELPWR_ENA ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELPWR_THRESH ; 
 int AR_PHY_RADAR_1_RELSTEP_CHECK ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_RELSTEP_THRESH ; 
 int AR_PHY_RADAR_1_USE_FIR128 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_EXT ; 
 int AR_PHY_RADAR_EXT_ENA ; 
 void* MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ar5416GetDfsThresh(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{
	uint32_t val, temp;

	val = OS_REG_READ(ah, AR_PHY_RADAR_0);

	temp = MS(val,AR_PHY_RADAR_0_FIRPWR);
	temp |= 0xFFFFFF80;
	pe->pe_firpwr = temp;
	pe->pe_rrssi = MS(val, AR_PHY_RADAR_0_RRSSI);
	pe->pe_height =  MS(val, AR_PHY_RADAR_0_HEIGHT);
	pe->pe_prssi = MS(val, AR_PHY_RADAR_0_PRSSI);
	pe->pe_inband = MS(val, AR_PHY_RADAR_0_INBAND);

	/* RADAR_1 values */
	val = OS_REG_READ(ah, AR_PHY_RADAR_1);
	pe->pe_relpwr = MS(val, AR_PHY_RADAR_1_RELPWR_THRESH);
	pe->pe_relstep = MS(val, AR_PHY_RADAR_1_RELSTEP_THRESH);
	pe->pe_maxlen = MS(val, AR_PHY_RADAR_1_MAXLEN);

	pe->pe_extchannel = !! (OS_REG_READ(ah, AR_PHY_RADAR_EXT) &
	    AR_PHY_RADAR_EXT_ENA);

	pe->pe_usefir128 = !! (OS_REG_READ(ah, AR_PHY_RADAR_1) &
	    AR_PHY_RADAR_1_USE_FIR128);
	pe->pe_blockradar = !! (OS_REG_READ(ah, AR_PHY_RADAR_1) &
	    AR_PHY_RADAR_1_BLOCK_CHECK);
	pe->pe_enmaxrssi = !! (OS_REG_READ(ah, AR_PHY_RADAR_1) &
	    AR_PHY_RADAR_1_MAX_RRSSI);
	pe->pe_enabled = !!
	    (OS_REG_READ(ah, AR_PHY_RADAR_0) & AR_PHY_RADAR_0_ENA);
	pe->pe_enrelpwr = !! (OS_REG_READ(ah, AR_PHY_RADAR_1) &
	    AR_PHY_RADAR_1_RELPWR_ENA);
	pe->pe_en_relstep_check = !! (OS_REG_READ(ah, AR_PHY_RADAR_1) &
	    AR_PHY_RADAR_1_RELSTEP_CHECK);
}