#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {int vdev_children; int vdev_isspare; scalar_t__ vdev_asize; scalar_t__ vdev_ashift; char* vdev_path; char* vdev_devid; int vdev_id; struct TYPE_38__* vdev_parent; struct TYPE_38__* vdev_top; int /*<<< orphan*/  vdev_crtxg; TYPE_2__* vdev_ops; scalar_t__ vdev_resilver_txg; int /*<<< orphan*/  vdev_guid; scalar_t__ vdev_islog; struct TYPE_38__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_39__ {int /*<<< orphan*/  vdev_op_leaf; } ;
typedef  TYPE_2__ vdev_ops_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_40__ {scalar_t__ spa_bootfs; int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/ * spa_vdev_removal; TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DTL_MISSING ; 
 int EBUSY ; 
 int EDOM ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOTSUP ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  ESC_ZFS_BOOTFS_VDEV_ATTACH ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_ATTACH ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_SPARE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 scalar_t__ SPA_VERSION_MULTI_REPLACE ; 
 scalar_t__ TXG_CONCURRENT_STATES ; 
 scalar_t__ TXG_INITIAL ; 
 int /*<<< orphan*/  VDD_DTL ; 
 int /*<<< orphan*/  VDEV_ALLOC_ATTACH ; 
 int ZFS_ERR_CHECKPOINT_EXISTS ; 
 int ZFS_ERR_DISCARDING_CHECKPOINT ; 
 int /*<<< orphan*/  dsl_resilver_restart (int /*<<< orphan*/ ,scalar_t__) ; 
 char* kmem_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int spa_config_parse (TYPE_3__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_active (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_has_checkpoint (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_has_spare (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 TYPE_1__* spa_lookup_by_guid (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_spare_activate (TYPE_1__*) ; 
 char* spa_strdup (char*) ; 
 int /*<<< orphan*/  spa_strfree (char*) ; 
 scalar_t__ spa_vdev_enter (TYPE_3__*) ; 
 int spa_vdev_exit (TYPE_3__*,TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ spa_version (TYPE_3__*) ; 
 int spa_writeable (TYPE_3__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vdev_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* vdev_add_parent (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_1__*) ; 
 int vdev_create (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  vdev_dirty (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vdev_dtl_dirty (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ vdev_get_min_asize (TYPE_1__*) ; 
 TYPE_2__ vdev_mirror_ops ; 
 int /*<<< orphan*/  vdev_remove_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_2__ vdev_replacing_ops ; 
 TYPE_2__ vdev_root_ops ; 
 TYPE_2__ vdev_spare_ops ; 

int
spa_vdev_attach(spa_t *spa, uint64_t guid, nvlist_t *nvroot, int replacing)
{
	uint64_t txg, dtl_max_txg;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *oldvd, *newvd, *newrootvd, *pvd, *tvd;
	vdev_ops_t *pvops;
	char *oldvdpath, *newvdpath;
	int newvd_isspare;
	int error;

	ASSERT(spa_writeable(spa));

	txg = spa_vdev_enter(spa);

	oldvd = spa_lookup_by_guid(spa, guid, B_FALSE);

	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	if (spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT)) {
		error = (spa_has_checkpoint(spa)) ?
		    ZFS_ERR_CHECKPOINT_EXISTS : ZFS_ERR_DISCARDING_CHECKPOINT;
		return (spa_vdev_exit(spa, NULL, txg, error));
	}

	if (spa->spa_vdev_removal != NULL)
		return (spa_vdev_exit(spa, NULL, txg, EBUSY));

	if (oldvd == NULL)
		return (spa_vdev_exit(spa, NULL, txg, ENODEV));

	if (!oldvd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_exit(spa, NULL, txg, ENOTSUP));

	pvd = oldvd->vdev_parent;

	if ((error = spa_config_parse(spa, &newrootvd, nvroot, NULL, 0,
	    VDEV_ALLOC_ATTACH)) != 0)
		return (spa_vdev_exit(spa, NULL, txg, EINVAL));

	if (newrootvd->vdev_children != 1)
		return (spa_vdev_exit(spa, newrootvd, txg, EINVAL));

	newvd = newrootvd->vdev_child[0];

	if (!newvd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_exit(spa, newrootvd, txg, EINVAL));

	if ((error = vdev_create(newrootvd, txg, replacing)) != 0)
		return (spa_vdev_exit(spa, newrootvd, txg, error));

	/*
	 * Spares can't replace logs
	 */
	if (oldvd->vdev_top->vdev_islog && newvd->vdev_isspare)
		return (spa_vdev_exit(spa, newrootvd, txg, ENOTSUP));

	if (!replacing) {
		/*
		 * For attach, the only allowable parent is a mirror or the root
		 * vdev.
		 */
		if (pvd->vdev_ops != &vdev_mirror_ops &&
		    pvd->vdev_ops != &vdev_root_ops)
			return (spa_vdev_exit(spa, newrootvd, txg, ENOTSUP));

		pvops = &vdev_mirror_ops;
	} else {
		/*
		 * Active hot spares can only be replaced by inactive hot
		 * spares.
		 */
		if (pvd->vdev_ops == &vdev_spare_ops &&
		    oldvd->vdev_isspare &&
		    !spa_has_spare(spa, newvd->vdev_guid))
			return (spa_vdev_exit(spa, newrootvd, txg, ENOTSUP));

		/*
		 * If the source is a hot spare, and the parent isn't already a
		 * spare, then we want to create a new hot spare.  Otherwise, we
		 * want to create a replacing vdev.  The user is not allowed to
		 * attach to a spared vdev child unless the 'isspare' state is
		 * the same (spare replaces spare, non-spare replaces
		 * non-spare).
		 */
		if (pvd->vdev_ops == &vdev_replacing_ops &&
		    spa_version(spa) < SPA_VERSION_MULTI_REPLACE) {
			return (spa_vdev_exit(spa, newrootvd, txg, ENOTSUP));
		} else if (pvd->vdev_ops == &vdev_spare_ops &&
		    newvd->vdev_isspare != oldvd->vdev_isspare) {
			return (spa_vdev_exit(spa, newrootvd, txg, ENOTSUP));
		}

		if (newvd->vdev_isspare)
			pvops = &vdev_spare_ops;
		else
			pvops = &vdev_replacing_ops;
	}

	/*
	 * Make sure the new device is big enough.
	 */
	if (newvd->vdev_asize < vdev_get_min_asize(oldvd))
		return (spa_vdev_exit(spa, newrootvd, txg, EOVERFLOW));

	/*
	 * The new device cannot have a higher alignment requirement
	 * than the top-level vdev.
	 */
	if (newvd->vdev_ashift > oldvd->vdev_top->vdev_ashift)
		return (spa_vdev_exit(spa, newrootvd, txg, EDOM));

	/*
	 * If this is an in-place replacement, update oldvd's path and devid
	 * to make it distinguishable from newvd, and unopenable from now on.
	 */
	if (strcmp(oldvd->vdev_path, newvd->vdev_path) == 0) {
		spa_strfree(oldvd->vdev_path);
		oldvd->vdev_path = kmem_alloc(strlen(newvd->vdev_path) + 5,
		    KM_SLEEP);
		(void) sprintf(oldvd->vdev_path, "%s/%s",
		    newvd->vdev_path, "old");
		if (oldvd->vdev_devid != NULL) {
			spa_strfree(oldvd->vdev_devid);
			oldvd->vdev_devid = NULL;
		}
	}

	/* mark the device being resilvered */
	newvd->vdev_resilver_txg = txg;

	/*
	 * If the parent is not a mirror, or if we're replacing, insert the new
	 * mirror/replacing/spare vdev above oldvd.
	 */
	if (pvd->vdev_ops != pvops)
		pvd = vdev_add_parent(oldvd, pvops);

	ASSERT(pvd->vdev_top->vdev_parent == rvd);
	ASSERT(pvd->vdev_ops == pvops);
	ASSERT(oldvd->vdev_parent == pvd);

	/*
	 * Extract the new device from its root and add it to pvd.
	 */
	vdev_remove_child(newrootvd, newvd);
	newvd->vdev_id = pvd->vdev_children;
	newvd->vdev_crtxg = oldvd->vdev_crtxg;
	vdev_add_child(pvd, newvd);

	tvd = newvd->vdev_top;
	ASSERT(pvd->vdev_top == tvd);
	ASSERT(tvd->vdev_parent == rvd);

	vdev_config_dirty(tvd);

	/*
	 * Set newvd's DTL to [TXG_INITIAL, dtl_max_txg) so that we account
	 * for any dmu_sync-ed blocks.  It will propagate upward when
	 * spa_vdev_exit() calls vdev_dtl_reassess().
	 */
	dtl_max_txg = txg + TXG_CONCURRENT_STATES;

	vdev_dtl_dirty(newvd, DTL_MISSING, TXG_INITIAL,
	    dtl_max_txg - TXG_INITIAL);

	if (newvd->vdev_isspare) {
		spa_spare_activate(newvd);
		spa_event_notify(spa, newvd, NULL, ESC_ZFS_VDEV_SPARE);
	}

	oldvdpath = spa_strdup(oldvd->vdev_path);
	newvdpath = spa_strdup(newvd->vdev_path);
	newvd_isspare = newvd->vdev_isspare;

	/*
	 * Mark newvd's DTL dirty in this txg.
	 */
	vdev_dirty(tvd, VDD_DTL, newvd, txg);

	/*
	 * Schedule the resilver to restart in the future. We do this to
	 * ensure that dmu_sync-ed blocks have been stitched into the
	 * respective datasets.
	 */
	dsl_resilver_restart(spa->spa_dsl_pool, dtl_max_txg);

	if (spa->spa_bootfs)
		spa_event_notify(spa, newvd, NULL, ESC_ZFS_BOOTFS_VDEV_ATTACH);

	spa_event_notify(spa, newvd, NULL, ESC_ZFS_VDEV_ATTACH);

	/*
	 * Commit the config
	 */
	(void) spa_vdev_exit(spa, newrootvd, dtl_max_txg, 0);

	spa_history_log_internal(spa, "vdev attach", NULL,
	    "%s vdev=%s %s vdev=%s",
	    replacing && newvd_isspare ? "spare in" :
	    replacing ? "replace" : "attach", newvdpath,
	    replacing ? "for" : "to", oldvdpath);

	spa_strfree(oldvdpath);
	spa_strfree(newvdpath);

	return (0);
}