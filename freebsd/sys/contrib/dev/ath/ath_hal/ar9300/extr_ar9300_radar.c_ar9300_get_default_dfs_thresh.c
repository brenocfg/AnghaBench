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
 int /*<<< orphan*/  AR9300_DFS_FIRPWR ; 
 int /*<<< orphan*/  AR9300_DFS_HEIGHT ; 
 int /*<<< orphan*/  AR9300_DFS_INBAND ; 
 int /*<<< orphan*/  AR9300_DFS_MAXLEN ; 
 int /*<<< orphan*/  AR9300_DFS_PRSSI ; 
 int /*<<< orphan*/  AR9300_DFS_RELPWR ; 
 int /*<<< orphan*/  AR9300_DFS_RELSTEP ; 
 int /*<<< orphan*/  AR9300_DFS_RRSSI ; 

HAL_BOOL
ar9300_get_default_dfs_thresh(struct ath_hal *ah, HAL_PHYERR_PARAM *pe)
{

    pe->pe_firpwr = AR9300_DFS_FIRPWR;
    pe->pe_rrssi = AR9300_DFS_RRSSI;
    pe->pe_height = AR9300_DFS_HEIGHT;
    pe->pe_prssi = AR9300_DFS_PRSSI;
    /* see prssi comment above */

    pe->pe_inband = AR9300_DFS_INBAND;
    pe->pe_relpwr = AR9300_DFS_RELPWR;
    pe->pe_relstep = AR9300_DFS_RELSTEP;
    pe->pe_maxlen = AR9300_DFS_MAXLEN;
    return (AH_TRUE);
}