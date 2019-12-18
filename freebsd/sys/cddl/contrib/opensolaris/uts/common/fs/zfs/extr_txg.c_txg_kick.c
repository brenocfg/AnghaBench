#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tx_quiesce_txg_waiting; scalar_t__ tx_open_txg; scalar_t__ tx_sync_txg_waiting; scalar_t__ tx_synced_txg; scalar_t__ tx_quiesced_txg; int /*<<< orphan*/  tx_sync_lock; int /*<<< orphan*/  tx_quiesce_more_cv; } ;
typedef  TYPE_1__ tx_state_t ;
struct TYPE_8__ {TYPE_1__ dp_tx; } ;
typedef  TYPE_2__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_config_held (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_is_quiescing (TYPE_2__*) ; 
 int /*<<< orphan*/  txg_is_syncing (TYPE_2__*) ; 

void
txg_kick(dsl_pool_t *dp)
{
	tx_state_t *tx = &dp->dp_tx;

	ASSERT(!dsl_pool_config_held(dp));

	mutex_enter(&tx->tx_sync_lock);
	if (!txg_is_syncing(dp) &&
	    !txg_is_quiescing(dp) &&
	    tx->tx_quiesce_txg_waiting <= tx->tx_open_txg &&
	    tx->tx_sync_txg_waiting <= tx->tx_synced_txg &&
	    tx->tx_quiesced_txg <= tx->tx_synced_txg) {
		tx->tx_quiesce_txg_waiting = tx->tx_open_txg + 1;
		cv_broadcast(&tx->tx_quiesce_more_cv);
	}
	mutex_exit(&tx->tx_sync_lock);
}