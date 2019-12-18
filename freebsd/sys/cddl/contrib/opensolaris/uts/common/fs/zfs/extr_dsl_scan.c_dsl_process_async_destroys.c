#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_21__ {int scn_async_destroying; int scn_async_stalled; scalar_t__ scn_visited_this_txg; int /*<<< orphan*/  scn_async_block_min_time_ms; void* scn_is_bptree; scalar_t__ scn_sync_start_time; int /*<<< orphan*/ * scn_zio_root; } ;
typedef  TYPE_1__ dsl_scan_t ;
struct TYPE_22__ {int /*<<< orphan*/  dp_obsolete_bpobj; int /*<<< orphan*/ * dp_spa; int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/ * dp_free_dir; int /*<<< orphan*/ * dp_leak_dir; int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/  dp_root_dir; scalar_t__ dp_bptree_obj; int /*<<< orphan*/  dp_free_bpobj; TYPE_1__* dp_scan; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_23__ {scalar_t__ tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_20__ {int /*<<< orphan*/  dd_uncompressed_bytes; int /*<<< orphan*/  dd_compressed_bytes; int /*<<< orphan*/  dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DD_USED_HEAD ; 
 int /*<<< orphan*/  DMU_POOL_BPTREE_OBJ ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_OBSOLETE_BPOBJ ; 
 int ECKSUM ; 
 int EIO ; 
 int /*<<< orphan*/  EQUIV (scalar_t__,int) ; 
 int ERESTART ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  LEAK_DIR_NAME ; 
 scalar_t__ NSEC2MSEC (scalar_t__) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_FLAG_MUSTSUCCEED ; 
 scalar_t__ bpobj_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ bpobj_is_open (int /*<<< orphan*/ *) ; 
 int bpobj_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bptree_free (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 scalar_t__ bptree_is_empty (int /*<<< orphan*/ ,scalar_t__) ; 
 int bptree_iterate (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ddt_sync (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dsl_dir_create_sync (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_11__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_destroy_obsolete_bpobj (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_pool_open_special_dir (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_scan_free_block_cb ; 
 int /*<<< orphan*/  dsl_scan_obsolete_block_cb ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_suspend_async_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 scalar_t__ zap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfs_free_bpobj_enabled ; 
 scalar_t__ zfs_free_leak_on_eio ; 
 int /*<<< orphan*/  zfs_free_min_time_ms ; 
 int /*<<< orphan*/  zfs_obsolete_min_time_ms ; 
 int /*<<< orphan*/  zfs_panic_recover (char*,int) ; 
 void* zio_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_process_async_destroys(dsl_pool_t *dp, dmu_tx_t *tx)
{
	int err = 0;
	dsl_scan_t *scn = dp->dp_scan;
	spa_t *spa = dp->dp_spa;

	if (spa_suspend_async_destroy(spa))
		return (0);

	if (zfs_free_bpobj_enabled &&
	    spa_version(spa) >= SPA_VERSION_DEADLISTS) {
		scn->scn_is_bptree = B_FALSE;
		scn->scn_async_block_min_time_ms = zfs_free_min_time_ms;
		scn->scn_zio_root = zio_root(spa, NULL,
		    NULL, ZIO_FLAG_MUSTSUCCEED);
		err = bpobj_iterate(&dp->dp_free_bpobj,
		    dsl_scan_free_block_cb, scn, tx);
		VERIFY0(zio_wait(scn->scn_zio_root));
		scn->scn_zio_root = NULL;

		if (err != 0 && err != ERESTART)
			zfs_panic_recover("error %u from bpobj_iterate()", err);
	}

	if (err == 0 && spa_feature_is_active(spa, SPA_FEATURE_ASYNC_DESTROY)) {
		ASSERT(scn->scn_async_destroying);
		scn->scn_is_bptree = B_TRUE;
		scn->scn_zio_root = zio_root(spa, NULL,
		    NULL, ZIO_FLAG_MUSTSUCCEED);
		err = bptree_iterate(dp->dp_meta_objset,
		    dp->dp_bptree_obj, B_TRUE, dsl_scan_free_block_cb, scn, tx);
		VERIFY0(zio_wait(scn->scn_zio_root));
		scn->scn_zio_root = NULL;

		if (err == EIO || err == ECKSUM) {
			err = 0;
		} else if (err != 0 && err != ERESTART) {
			zfs_panic_recover("error %u from "
			    "traverse_dataset_destroyed()", err);
		}

		if (bptree_is_empty(dp->dp_meta_objset, dp->dp_bptree_obj)) {
			/* finished; deactivate async destroy feature */
			spa_feature_decr(spa, SPA_FEATURE_ASYNC_DESTROY, tx);
			ASSERT(!spa_feature_is_active(spa,
			    SPA_FEATURE_ASYNC_DESTROY));
			VERIFY0(zap_remove(dp->dp_meta_objset,
			    DMU_POOL_DIRECTORY_OBJECT,
			    DMU_POOL_BPTREE_OBJ, tx));
			VERIFY0(bptree_free(dp->dp_meta_objset,
			    dp->dp_bptree_obj, tx));
			dp->dp_bptree_obj = 0;
			scn->scn_async_destroying = B_FALSE;
			scn->scn_async_stalled = B_FALSE;
		} else {
			/*
			 * If we didn't make progress, mark the async
			 * destroy as stalled, so that we will not initiate
			 * a spa_sync() on its behalf.  Note that we only
			 * check this if we are not finished, because if the
			 * bptree had no blocks for us to visit, we can
			 * finish without "making progress".
			 */
			scn->scn_async_stalled =
			    (scn->scn_visited_this_txg == 0);
		}
	}
	if (scn->scn_visited_this_txg) {
		zfs_dbgmsg("freed %llu blocks in %llums from "
		    "free_bpobj/bptree txg %llu; err=%d",
		    (longlong_t)scn->scn_visited_this_txg,
		    (longlong_t)
		    NSEC2MSEC(gethrtime() - scn->scn_sync_start_time),
		    (longlong_t)tx->tx_txg, err);
		scn->scn_visited_this_txg = 0;

		/*
		 * Write out changes to the DDT that may be required as a
		 * result of the blocks freed.  This ensures that the DDT
		 * is clean when a scrub/resilver runs.
		 */
		ddt_sync(spa, tx->tx_txg);
	}
	if (err != 0)
		return (err);
	if (dp->dp_free_dir != NULL && !scn->scn_async_destroying &&
	    zfs_free_leak_on_eio &&
	    (dsl_dir_phys(dp->dp_free_dir)->dd_used_bytes != 0 ||
	    dsl_dir_phys(dp->dp_free_dir)->dd_compressed_bytes != 0 ||
	    dsl_dir_phys(dp->dp_free_dir)->dd_uncompressed_bytes != 0)) {
		/*
		 * We have finished background destroying, but there is still
		 * some space left in the dp_free_dir. Transfer this leaked
		 * space to the dp_leak_dir.
		 */
		if (dp->dp_leak_dir == NULL) {
			rrw_enter(&dp->dp_config_rwlock, RW_WRITER, FTAG);
			(void) dsl_dir_create_sync(dp, dp->dp_root_dir,
			    LEAK_DIR_NAME, tx);
			VERIFY0(dsl_pool_open_special_dir(dp,
			    LEAK_DIR_NAME, &dp->dp_leak_dir));
			rrw_exit(&dp->dp_config_rwlock, FTAG);
		}
		dsl_dir_diduse_space(dp->dp_leak_dir, DD_USED_HEAD,
		    dsl_dir_phys(dp->dp_free_dir)->dd_used_bytes,
		    dsl_dir_phys(dp->dp_free_dir)->dd_compressed_bytes,
		    dsl_dir_phys(dp->dp_free_dir)->dd_uncompressed_bytes, tx);
		dsl_dir_diduse_space(dp->dp_free_dir, DD_USED_HEAD,
		    -dsl_dir_phys(dp->dp_free_dir)->dd_used_bytes,
		    -dsl_dir_phys(dp->dp_free_dir)->dd_compressed_bytes,
		    -dsl_dir_phys(dp->dp_free_dir)->dd_uncompressed_bytes, tx);
	}

	if (dp->dp_free_dir != NULL && !scn->scn_async_destroying) {
		/* finished; verify that space accounting went to zero */
		ASSERT0(dsl_dir_phys(dp->dp_free_dir)->dd_used_bytes);
		ASSERT0(dsl_dir_phys(dp->dp_free_dir)->dd_compressed_bytes);
		ASSERT0(dsl_dir_phys(dp->dp_free_dir)->dd_uncompressed_bytes);
	}

	EQUIV(bpobj_is_open(&dp->dp_obsolete_bpobj),
	    0 == zap_contains(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_OBSOLETE_BPOBJ));
	if (err == 0 && bpobj_is_open(&dp->dp_obsolete_bpobj)) {
		ASSERT(spa_feature_is_active(dp->dp_spa,
		    SPA_FEATURE_OBSOLETE_COUNTS));

		scn->scn_is_bptree = B_FALSE;
		scn->scn_async_block_min_time_ms = zfs_obsolete_min_time_ms;
		err = bpobj_iterate(&dp->dp_obsolete_bpobj,
		    dsl_scan_obsolete_block_cb, scn, tx);
		if (err != 0 && err != ERESTART)
			zfs_panic_recover("error %u from bpobj_iterate()", err);

		if (bpobj_is_empty(&dp->dp_obsolete_bpobj))
			dsl_pool_destroy_obsolete_bpobj(dp, tx);
	}

	return (0);
}