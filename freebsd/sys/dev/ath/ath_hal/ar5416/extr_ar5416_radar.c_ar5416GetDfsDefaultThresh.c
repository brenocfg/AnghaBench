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
struct TYPE_3__ {int /*<<< orphan*/  pe_maxlen; int /*<<< orphan*/  pe_relstep; int /*<<< orphan*/  pe_relpwr; int /*<<< orphan*/  pe_inband; int /*<<< orphan*/  pe_prssi; int /*<<< orphan*/  pe_height; int /*<<< orphan*/  pe_rrssi; int /*<<< orphan*/  pe_firpwr; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR5416_DFS_FIRPWR ; 
 int /*<<< orphan*/  AR5416_DFS_HEIGHT ; 
 int /*<<< orphan*/  AR5416_DFS_INBAND ; 
 int /*<<< orphan*/  AR5416_DFS_MAXLEN ; 
 int /*<<< orphan*/  AR5416_DFS_PRSSI ; 
 int /*<<< orphan*/  AR5416_DFS_RELPWR ; 
 int /*<<< orphan*/  AR5416_DFS_RELSTEP ; 
 int /*<<< orphan*/  AR5416_DFS_RRSSI ; 

HAL_BOOL
ar5416GetDfsDefaultThresh(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{

	/*
	 * These are general examples of the parameter values
	 * to use when configuring radar pulse detection for
	 * the AR5416, AR91xx, AR92xx NICs.  They are only
	 * for testing and do require tuning depending upon the
	 * hardware and deployment specifics.
	 */
	pe->pe_firpwr = AR5416_DFS_FIRPWR;
	pe->pe_rrssi = AR5416_DFS_RRSSI;
	pe->pe_height = AR5416_DFS_HEIGHT;
	pe->pe_prssi = AR5416_DFS_PRSSI;
	pe->pe_inband = AR5416_DFS_INBAND;
	pe->pe_relpwr = AR5416_DFS_RELPWR;
	pe->pe_relstep = AR5416_DFS_RELSTEP;
	pe->pe_maxlen = AR5416_DFS_MAXLEN;

	return (AH_TRUE);
}