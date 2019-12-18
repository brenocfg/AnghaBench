#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {scalar_t__ tx_txg; int /*<<< orphan*/  tx_txgh; int /*<<< orphan*/  tx_dirty_delayed; int /*<<< orphan*/  tx_pool; } ;
typedef  TYPE_1__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ERESTART ; 
 int /*<<< orphan*/  IMPLY (int,int) ; 
 int TXG_NOTHROTTLE ; 
 int TXG_WAIT ; 
 int dmu_tx_try_assign (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dmu_tx_unassign (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_rele_to_quiesce (int /*<<< orphan*/ *) ; 

int
dmu_tx_assign(dmu_tx_t *tx, uint64_t txg_how)
{
	int err;

	ASSERT(tx->tx_txg == 0);
	ASSERT0(txg_how & ~(TXG_WAIT | TXG_NOTHROTTLE));
	ASSERT(!dsl_pool_sync_context(tx->tx_pool));

	/* If we might wait, we must not hold the config lock. */
	IMPLY((txg_how & TXG_WAIT), !dsl_pool_config_held(tx->tx_pool));

	if ((txg_how & TXG_NOTHROTTLE))
		tx->tx_dirty_delayed = B_TRUE;

	while ((err = dmu_tx_try_assign(tx, txg_how)) != 0) {
		dmu_tx_unassign(tx);

		if (err != ERESTART || !(txg_how & TXG_WAIT))
			return (err);

		dmu_tx_wait(tx);
	}

	txg_rele_to_quiesce(&tx->tx_txgh);

	return (0);
}