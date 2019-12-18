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
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int pe_blockradar; int pe_enmaxrssi; int pe_enrelpwr; scalar_t__ pe_en_relstep_check; scalar_t__ pe_usefir128; scalar_t__ pe_maxlen; scalar_t__ pe_relstep; scalar_t__ pe_relpwr; int /*<<< orphan*/  pe_inband; int /*<<< orphan*/  pe_prssi; int /*<<< orphan*/  pe_height; int /*<<< orphan*/  pe_rrssi; int /*<<< orphan*/  pe_firpwr; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR5212_DFS_FIRPWR ; 
 int /*<<< orphan*/  AR5212_DFS_HEIGHT ; 
 int /*<<< orphan*/  AR5212_DFS_INBAND ; 
 int /*<<< orphan*/  AR5212_DFS_PRSSI ; 
 int /*<<< orphan*/  AR5212_DFS_RRSSI ; 
 int /*<<< orphan*/  AR5413_DFS_FIRPWR ; 
 int /*<<< orphan*/  AR5413_DFS_HEIGHT ; 
 int /*<<< orphan*/  AR5413_DFS_INBAND ; 
 scalar_t__ AR5413_DFS_MAXLEN ; 
 int /*<<< orphan*/  AR5413_DFS_PRSSI ; 
 scalar_t__ AR5413_DFS_RELPWR ; 
 scalar_t__ AR5413_DFS_RELSTEP ; 
 int /*<<< orphan*/  AR5413_DFS_RRSSI ; 
 scalar_t__ IS_5413 (struct ath_hal*) ; 

HAL_BOOL
ar5212GetDfsDefaultThresh(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{

	if (IS_5413(ah)) {
		pe->pe_firpwr = AR5413_DFS_FIRPWR;
		pe->pe_rrssi = AR5413_DFS_RRSSI;
		pe->pe_height = AR5413_DFS_HEIGHT;
		pe->pe_prssi = AR5413_DFS_PRSSI;
		pe->pe_inband = AR5413_DFS_INBAND;
		pe->pe_relpwr = AR5413_DFS_RELPWR;
		pe->pe_relstep = AR5413_DFS_RELSTEP;
		pe->pe_maxlen = AR5413_DFS_MAXLEN;
		pe->pe_usefir128 = 0;
		pe->pe_blockradar = 1;
		pe->pe_enmaxrssi = 1;
		pe->pe_enrelpwr = 1;
		pe->pe_en_relstep_check = 0;
	} else {
		pe->pe_firpwr = AR5212_DFS_FIRPWR;
		pe->pe_rrssi = AR5212_DFS_RRSSI;
		pe->pe_height = AR5212_DFS_HEIGHT;
		pe->pe_prssi = AR5212_DFS_PRSSI;
		pe->pe_inband = AR5212_DFS_INBAND;
		pe->pe_relpwr = 0;
		pe->pe_relstep = 0;
		pe->pe_maxlen = 0;
		pe->pe_usefir128 = 0;
		pe->pe_blockradar = 0;
		pe->pe_enmaxrssi = 0;
		pe->pe_enrelpwr = 0;
		pe->pe_en_relstep_check = 0;
	}

	return (AH_TRUE);
}