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
struct ath_hal {int /*<<< orphan*/  (* ah_setDfsCacTxQuiet ) (struct ath_hal*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ath_hal_set_dfs_cac_tx_quiet(struct ath_hal *ah, HAL_BOOL ena)
{

	if (ah->ah_setDfsCacTxQuiet == NULL)
		return;
	ah->ah_setDfsCacTxQuiet(ah, ena);
}