#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {TYPE_1__* dp_scan; int /*<<< orphan*/  dp_mos_dir; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_4__ {scalar_t__ scn_restart_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_dd (int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,scalar_t__) ; 

void
dsl_resilver_restart(dsl_pool_t *dp, uint64_t txg)
{
	if (txg == 0) {
		dmu_tx_t *tx;
		tx = dmu_tx_create_dd(dp->dp_mos_dir);
		VERIFY(0 == dmu_tx_assign(tx, TXG_WAIT));

		txg = dmu_tx_get_txg(tx);
		dp->dp_scan->scn_restart_txg = txg;
		dmu_tx_commit(tx);
	} else {
		dp->dp_scan->scn_restart_txg = txg;
	}
	zfs_dbgmsg("restarting resilver txg=%llu", txg);
}