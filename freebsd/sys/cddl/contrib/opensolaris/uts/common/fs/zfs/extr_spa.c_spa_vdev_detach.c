#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
struct TYPE_39__ {scalar_t__ vdev_guid; int vdev_children; scalar_t__ vdev_id; char* vdev_path; int vdev_isspare; void* vdev_detached; int /*<<< orphan*/  vdev_dtl_list; struct TYPE_39__* vdev_parent; struct TYPE_39__* vdev_top; void* vdev_unspare; TYPE_3__* vdev_ops; struct TYPE_39__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_40__ {scalar_t__ spa_state; scalar_t__ spa_autoexpand; TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  void* boolean_t ;
struct TYPE_41__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_REMOVE ; 
 int /*<<< orphan*/  FTAG ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ POOL_STATE_ACTIVE ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 scalar_t__ SPA_VERSION_SPARES ; 
 int TXG_SIZE ; 
 int /*<<< orphan*/  VDD_DTL ; 
 int /*<<< orphan*/  VDEV_LABEL_REMOVE ; 
 int ZFS_ERR_CHECKPOINT_EXISTS ; 
 int ZFS_ERR_DISCARDING_CHECKPOINT ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_active (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_has_checkpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_1__* spa_lookup_by_guid (TYPE_2__*,scalar_t__,void*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_2__* spa_next (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_open_ref (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_spare_remove (TYPE_1__*) ; 
 void* spa_strdup (char*) ; 
 int /*<<< orphan*/  spa_strfree (char*) ; 
 scalar_t__ spa_vdev_enter (TYPE_2__*) ; 
 int spa_vdev_exit (TYPE_2__*,TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  spa_vdev_remove (TYPE_2__*,scalar_t__,void*) ; 
 int /*<<< orphan*/  spa_vdev_resilver_done (TYPE_2__*) ; 
 scalar_t__ spa_version (TYPE_2__*) ; 
 int spa_writeable (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  txg_list_remove_this (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vdev_compact_children (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_dirty (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ vdev_dtl_required (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_expand (TYPE_1__*,scalar_t__) ; 
 int vdev_label_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ vdev_mirror_ops ; 
 int /*<<< orphan*/  vdev_propagate_state (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_remove_child (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_remove_parent (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_1__*) ; 
 TYPE_3__ vdev_replacing_ops ; 
 TYPE_3__ vdev_spare_ops ; 

int
spa_vdev_detach(spa_t *spa, uint64_t guid, uint64_t pguid, int replace_done)
{
	uint64_t txg;
	int error;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *vd, *pvd, *cvd, *tvd;
	boolean_t unspare = B_FALSE;
	uint64_t unspare_guid = 0;
	char *vdpath;

	ASSERT(spa_writeable(spa));

	txg = spa_vdev_enter(spa);

	vd = spa_lookup_by_guid(spa, guid, B_FALSE);

	/*
	 * Besides being called directly from the userland through the
	 * ioctl interface, spa_vdev_detach() can be potentially called
	 * at the end of spa_vdev_resilver_done().
	 *
	 * In the regular case, when we have a checkpoint this shouldn't
	 * happen as we never empty the DTLs of a vdev during the scrub
	 * [see comment in dsl_scan_done()]. Thus spa_vdev_resilvering_done()
	 * should never get here when we have a checkpoint.
	 *
	 * That said, even in a case when we checkpoint the pool exactly
	 * as spa_vdev_resilver_done() calls this function everything
	 * should be fine as the resilver will return right away.
	 */
	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	if (spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT)) {
		error = (spa_has_checkpoint(spa)) ?
		    ZFS_ERR_CHECKPOINT_EXISTS : ZFS_ERR_DISCARDING_CHECKPOINT;
		return (spa_vdev_exit(spa, NULL, txg, error));
	}

	if (vd == NULL)
		return (spa_vdev_exit(spa, NULL, txg, ENODEV));

	if (!vd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_exit(spa, NULL, txg, ENOTSUP));

	pvd = vd->vdev_parent;

	/*
	 * If the parent/child relationship is not as expected, don't do it.
	 * Consider M(A,R(B,C)) -- that is, a mirror of A with a replacing
	 * vdev that's replacing B with C.  The user's intent in replacing
	 * is to go from M(A,B) to M(A,C).  If the user decides to cancel
	 * the replace by detaching C, the expected behavior is to end up
	 * M(A,B).  But suppose that right after deciding to detach C,
	 * the replacement of B completes.  We would have M(A,C), and then
	 * ask to detach C, which would leave us with just A -- not what
	 * the user wanted.  To prevent this, we make sure that the
	 * parent/child relationship hasn't changed -- in this example,
	 * that C's parent is still the replacing vdev R.
	 */
	if (pvd->vdev_guid != pguid && pguid != 0)
		return (spa_vdev_exit(spa, NULL, txg, EBUSY));

	/*
	 * Only 'replacing' or 'spare' vdevs can be replaced.
	 */
	if (replace_done && pvd->vdev_ops != &vdev_replacing_ops &&
	    pvd->vdev_ops != &vdev_spare_ops)
		return (spa_vdev_exit(spa, NULL, txg, ENOTSUP));

	ASSERT(pvd->vdev_ops != &vdev_spare_ops ||
	    spa_version(spa) >= SPA_VERSION_SPARES);

	/*
	 * Only mirror, replacing, and spare vdevs support detach.
	 */
	if (pvd->vdev_ops != &vdev_replacing_ops &&
	    pvd->vdev_ops != &vdev_mirror_ops &&
	    pvd->vdev_ops != &vdev_spare_ops)
		return (spa_vdev_exit(spa, NULL, txg, ENOTSUP));

	/*
	 * If this device has the only valid copy of some data,
	 * we cannot safely detach it.
	 */
	if (vdev_dtl_required(vd))
		return (spa_vdev_exit(spa, NULL, txg, EBUSY));

	ASSERT(pvd->vdev_children >= 2);

	/*
	 * If we are detaching the second disk from a replacing vdev, then
	 * check to see if we changed the original vdev's path to have "/old"
	 * at the end in spa_vdev_attach().  If so, undo that change now.
	 */
	if (pvd->vdev_ops == &vdev_replacing_ops && vd->vdev_id > 0 &&
	    vd->vdev_path != NULL) {
		size_t len = strlen(vd->vdev_path);

		for (int c = 0; c < pvd->vdev_children; c++) {
			cvd = pvd->vdev_child[c];

			if (cvd == vd || cvd->vdev_path == NULL)
				continue;

			if (strncmp(cvd->vdev_path, vd->vdev_path, len) == 0 &&
			    strcmp(cvd->vdev_path + len, "/old") == 0) {
				spa_strfree(cvd->vdev_path);
				cvd->vdev_path = spa_strdup(vd->vdev_path);
				break;
			}
		}
	}

	/*
	 * If we are detaching the original disk from a spare, then it implies
	 * that the spare should become a real disk, and be removed from the
	 * active spare list for the pool.
	 */
	if (pvd->vdev_ops == &vdev_spare_ops &&
	    vd->vdev_id == 0 &&
	    pvd->vdev_child[pvd->vdev_children - 1]->vdev_isspare)
		unspare = B_TRUE;

	/*
	 * Erase the disk labels so the disk can be used for other things.
	 * This must be done after all other error cases are handled,
	 * but before we disembowel vd (so we can still do I/O to it).
	 * But if we can't do it, don't treat the error as fatal --
	 * it may be that the unwritability of the disk is the reason
	 * it's being detached!
	 */
	error = vdev_label_init(vd, 0, VDEV_LABEL_REMOVE);

	/*
	 * Remove vd from its parent and compact the parent's children.
	 */
	vdev_remove_child(pvd, vd);
	vdev_compact_children(pvd);

	/*
	 * Remember one of the remaining children so we can get tvd below.
	 */
	cvd = pvd->vdev_child[pvd->vdev_children - 1];

	/*
	 * If we need to remove the remaining child from the list of hot spares,
	 * do it now, marking the vdev as no longer a spare in the process.
	 * We must do this before vdev_remove_parent(), because that can
	 * change the GUID if it creates a new toplevel GUID.  For a similar
	 * reason, we must remove the spare now, in the same txg as the detach;
	 * otherwise someone could attach a new sibling, change the GUID, and
	 * the subsequent attempt to spa_vdev_remove(unspare_guid) would fail.
	 */
	if (unspare) {
		ASSERT(cvd->vdev_isspare);
		spa_spare_remove(cvd);
		unspare_guid = cvd->vdev_guid;
		(void) spa_vdev_remove(spa, unspare_guid, B_TRUE);
		cvd->vdev_unspare = B_TRUE;
	}

	/*
	 * If the parent mirror/replacing vdev only has one child,
	 * the parent is no longer needed.  Remove it from the tree.
	 */
	if (pvd->vdev_children == 1) {
		if (pvd->vdev_ops == &vdev_spare_ops)
			cvd->vdev_unspare = B_FALSE;
		vdev_remove_parent(cvd);
	}


	/*
	 * We don't set tvd until now because the parent we just removed
	 * may have been the previous top-level vdev.
	 */
	tvd = cvd->vdev_top;
	ASSERT(tvd->vdev_parent == rvd);

	/*
	 * Reevaluate the parent vdev state.
	 */
	vdev_propagate_state(cvd);

	/*
	 * If the 'autoexpand' property is set on the pool then automatically
	 * try to expand the size of the pool. For example if the device we
	 * just detached was smaller than the others, it may be possible to
	 * add metaslabs (i.e. grow the pool). We need to reopen the vdev
	 * first so that we can obtain the updated sizes of the leaf vdevs.
	 */
	if (spa->spa_autoexpand) {
		vdev_reopen(tvd);
		vdev_expand(tvd, txg);
	}

	vdev_config_dirty(tvd);

	/*
	 * Mark vd's DTL as dirty in this txg.  vdev_dtl_sync() will see that
	 * vd->vdev_detached is set and free vd's DTL object in syncing context.
	 * But first make sure we're not on any *other* txg's DTL list, to
	 * prevent vd from being accessed after it's freed.
	 */
	vdpath = spa_strdup(vd->vdev_path);
	for (int t = 0; t < TXG_SIZE; t++)
		(void) txg_list_remove_this(&tvd->vdev_dtl_list, vd, t);
	vd->vdev_detached = B_TRUE;
	vdev_dirty(tvd, VDD_DTL, vd, txg);

	spa_event_notify(spa, vd, NULL, ESC_ZFS_VDEV_REMOVE);

	/* hang on to the spa before we release the lock */
	spa_open_ref(spa, FTAG);

	error = spa_vdev_exit(spa, vd, txg, 0);

	spa_history_log_internal(spa, "detach", NULL,
	    "vdev=%s", vdpath);
	spa_strfree(vdpath);

	/*
	 * If this was the removal of the original device in a hot spare vdev,
	 * then we want to go through and remove the device from the hot spare
	 * list of every other pool.
	 */
	if (unspare) {
		spa_t *altspa = NULL;

		mutex_enter(&spa_namespace_lock);
		while ((altspa = spa_next(altspa)) != NULL) {
			if (altspa->spa_state != POOL_STATE_ACTIVE ||
			    altspa == spa)
				continue;

			spa_open_ref(altspa, FTAG);
			mutex_exit(&spa_namespace_lock);
			(void) spa_vdev_remove(altspa, unspare_guid, B_TRUE);
			mutex_enter(&spa_namespace_lock);
			spa_close(altspa, FTAG);
		}
		mutex_exit(&spa_namespace_lock);

		/* search the rest of the vdevs for spares to remove */
		spa_vdev_resilver_done(spa);
	}

	/* all done with the spa; OK to release */
	mutex_enter(&spa_namespace_lock);
	spa_close(spa, FTAG);
	mutex_exit(&spa_namespace_lock);

	return (error);
}