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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int pe_firpwr; int pe_enabled; int pe_enrelpwr; int pe_en_relstep_check; void* pe_maxlen; void* pe_relstep; void* pe_relpwr; void* pe_inband; void* pe_prssi; void* pe_height; void* pe_rrssi; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int AR_PHY_RADAR_0_ENA ; 
 int AR_PHY_RADAR_0_FIRPWR ; 
 int AR_PHY_RADAR_0_FIRPWR_S ; 
 int AR_PHY_RADAR_0_HEIGHT ; 
 int AR_PHY_RADAR_0_INBAND ; 
 int AR_PHY_RADAR_0_PRSSI ; 
 int AR_PHY_RADAR_0_RRSSI ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1 ; 
 int AR_PHY_RADAR_1_MAXLEN ; 
 int AR_PHY_RADAR_1_RELPWR_ENA ; 
 int AR_PHY_RADAR_1_RELPWR_THRESH ; 
 int AR_PHY_RADAR_1_RELSTEP_CHECK ; 
 int AR_PHY_RADAR_1_RELSTEP_THRESH ; 
 void* MS (int,int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ar9300_get_dfs_thresh(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{
    u_int32_t val, temp;

    val = OS_REG_READ(ah, AR_PHY_RADAR_0);
    temp = MS(val, AR_PHY_RADAR_0_FIRPWR);
    temp |= ~(AR_PHY_RADAR_0_FIRPWR >> AR_PHY_RADAR_0_FIRPWR_S);
    pe->pe_firpwr = temp;
    pe->pe_rrssi = MS(val, AR_PHY_RADAR_0_RRSSI);
    pe->pe_height = MS(val, AR_PHY_RADAR_0_HEIGHT);
    pe->pe_prssi = MS(val, AR_PHY_RADAR_0_PRSSI);
    pe->pe_inband = MS(val, AR_PHY_RADAR_0_INBAND);
    pe->pe_enabled = !! MS(val, AR_PHY_RADAR_0_ENA);

    val = OS_REG_READ(ah, AR_PHY_RADAR_1);

    pe->pe_relpwr = MS(val, AR_PHY_RADAR_1_RELPWR_THRESH);
    pe->pe_enrelpwr = !! (val & AR_PHY_RADAR_1_RELPWR_ENA);

    pe->pe_relstep = MS(val, AR_PHY_RADAR_1_RELSTEP_THRESH);
    pe->pe_en_relstep_check = !! (val & AR_PHY_RADAR_1_RELSTEP_CHECK);

    pe->pe_maxlen = MS(val, AR_PHY_RADAR_1_MAXLEN);
}