#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  spa_claiming; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_11__ {int /*<<< orphan*/  dp_root_dir_obj; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int /*<<< orphan*/  SPA_LOG_GOOD ; 
 int /*<<< orphan*/  dmu_objset_find_dp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_assigned (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_first_txg (TYPE_1__*) ; 
 TYPE_2__* spa_get_dsl (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_set_log_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_claim ; 

__attribute__((used)) static void
spa_ld_claim_log_blocks(spa_t *spa)
{
	dmu_tx_t *tx;
	dsl_pool_t *dp = spa_get_dsl(spa);

	/*
	 * Claim log blocks that haven't been committed yet.
	 * This must all happen in a single txg.
	 * Note: spa_claim_max_txg is updated by spa_claim_notify(),
	 * invoked from zil_claim_log_block()'s i/o done callback.
	 * Price of rollback is that we abandon the log.
	 */
	spa->spa_claiming = B_TRUE;

	tx = dmu_tx_create_assigned(dp, spa_first_txg(spa));
	(void) dmu_objset_find_dp(dp, dp->dp_root_dir_obj,
	    zil_claim, tx, DS_FIND_CHILDREN);
	dmu_tx_commit(tx);

	spa->spa_claiming = B_FALSE;

	spa_set_log_state(spa, SPA_LOG_GOOD);
}