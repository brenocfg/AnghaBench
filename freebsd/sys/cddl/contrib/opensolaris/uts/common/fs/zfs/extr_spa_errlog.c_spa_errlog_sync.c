#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int spa_scrub_finished; int /*<<< orphan*/  spa_errlog_lock; int /*<<< orphan*/  spa_errlog_scrub; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_errlog_last; int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_errlist_lock; int /*<<< orphan*/  spa_errlist_last; int /*<<< orphan*/  spa_errlist_scrub; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int B_FALSE ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ERRLOG_LAST ; 
 int /*<<< orphan*/  DMU_POOL_ERRLOG_SCRUB ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_object_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_assigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_errlists (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_error_list (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
spa_errlog_sync(spa_t *spa, uint64_t txg)
{
	dmu_tx_t *tx;
	avl_tree_t scrub, last;
	int scrub_finished;

	mutex_enter(&spa->spa_errlist_lock);

	/*
	 * Bail out early under normal circumstances.
	 */
	if (avl_numnodes(&spa->spa_errlist_scrub) == 0 &&
	    avl_numnodes(&spa->spa_errlist_last) == 0 &&
	    !spa->spa_scrub_finished) {
		mutex_exit(&spa->spa_errlist_lock);
		return;
	}

	spa_get_errlists(spa, &last, &scrub);
	scrub_finished = spa->spa_scrub_finished;
	spa->spa_scrub_finished = B_FALSE;

	mutex_exit(&spa->spa_errlist_lock);
	mutex_enter(&spa->spa_errlog_lock);

	tx = dmu_tx_create_assigned(spa->spa_dsl_pool, txg);

	/*
	 * Sync out the current list of errors.
	 */
	sync_error_list(spa, &last, &spa->spa_errlog_last, tx);

	/*
	 * Rotate the log if necessary.
	 */
	if (scrub_finished) {
		if (spa->spa_errlog_last != 0)
			VERIFY(dmu_object_free(spa->spa_meta_objset,
			    spa->spa_errlog_last, tx) == 0);
		spa->spa_errlog_last = spa->spa_errlog_scrub;
		spa->spa_errlog_scrub = 0;

		sync_error_list(spa, &scrub, &spa->spa_errlog_last, tx);
	}

	/*
	 * Sync out any pending scrub errors.
	 */
	sync_error_list(spa, &scrub, &spa->spa_errlog_scrub, tx);

	/*
	 * Update the MOS to reflect the new values.
	 */
	(void) zap_update(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_ERRLOG_LAST, sizeof (uint64_t), 1,
	    &spa->spa_errlog_last, tx);
	(void) zap_update(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_ERRLOG_SCRUB, sizeof (uint64_t), 1,
	    &spa->spa_errlog_scrub, tx);

	dmu_tx_commit(tx);

	mutex_exit(&spa->spa_errlog_lock);
}