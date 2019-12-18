#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_19__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ vdev_children; scalar_t__ vdev_ashift; size_t vdev_id; struct TYPE_28__** vdev_child; scalar_t__ vdev_ishole; TYPE_6__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint_t ;
typedef  size_t uint64_t ;
struct TYPE_26__ {void* sav_sync; } ;
struct TYPE_27__ {int sr_prev_indirect_vdev; } ;
struct TYPE_29__ {scalar_t__ spa_max_ashift; TYPE_19__ spa_l2cache; TYPE_19__ spa_spares; int /*<<< orphan*/ * spa_vdev_removal; TYPE_1__ spa_removing_phys; TYPE_2__* spa_pending_vdev; TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_30__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 void* B_TRUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_ADD ; 
 int /*<<< orphan*/  SPA_CONFIG_UPDATE_POOL ; 
 int /*<<< orphan*/  VDEV_ALLOC_ADD ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,scalar_t__*) ; 
 int spa_config_parse (TYPE_3__*,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_update (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_l2cache (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_load_spares (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_set_aux_vdevs (TYPE_19__*,int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ) ; 
 int spa_validate_aux (TYPE_3__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t spa_vdev_enter (TYPE_3__*) ; 
 int spa_vdev_exit (TYPE_3__*,TYPE_2__*,size_t,int) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_add_child (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_2__*) ; 
 int vdev_create (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_free (TYPE_2__*) ; 
 TYPE_6__ vdev_mirror_ops ; 
 TYPE_6__ vdev_raidz_ops ; 
 int /*<<< orphan*/  vdev_remove_child (TYPE_2__*,TYPE_2__*) ; 

int
spa_vdev_add(spa_t *spa, nvlist_t *nvroot)
{
	uint64_t txg, id;
	int error;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *vd, *tvd;
	nvlist_t **spares, **l2cache;
	uint_t nspares, nl2cache;

	ASSERT(spa_writeable(spa));

	txg = spa_vdev_enter(spa);

	if ((error = spa_config_parse(spa, &vd, nvroot, NULL, 0,
	    VDEV_ALLOC_ADD)) != 0)
		return (spa_vdev_exit(spa, NULL, txg, error));

	spa->spa_pending_vdev = vd;	/* spa_vdev_exit() will clear this */

	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_SPARES, &spares,
	    &nspares) != 0)
		nspares = 0;

	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_L2CACHE, &l2cache,
	    &nl2cache) != 0)
		nl2cache = 0;

	if (vd->vdev_children == 0 && nspares == 0 && nl2cache == 0)
		return (spa_vdev_exit(spa, vd, txg, EINVAL));

	if (vd->vdev_children != 0 &&
	    (error = vdev_create(vd, txg, B_FALSE)) != 0)
		return (spa_vdev_exit(spa, vd, txg, error));

	/*
	 * We must validate the spares and l2cache devices after checking the
	 * children.  Otherwise, vdev_inuse() will blindly overwrite the spare.
	 */
	if ((error = spa_validate_aux(spa, nvroot, txg, VDEV_ALLOC_ADD)) != 0)
		return (spa_vdev_exit(spa, vd, txg, error));

	/*
	 * If we are in the middle of a device removal, we can only add
	 * devices which match the existing devices in the pool.
	 * If we are in the middle of a removal, or have some indirect
	 * vdevs, we can not add raidz toplevels.
	 */
	if (spa->spa_vdev_removal != NULL ||
	    spa->spa_removing_phys.sr_prev_indirect_vdev != -1) {
		for (int c = 0; c < vd->vdev_children; c++) {
			tvd = vd->vdev_child[c];
			if (spa->spa_vdev_removal != NULL &&
			    tvd->vdev_ashift != spa->spa_max_ashift) {
				return (spa_vdev_exit(spa, vd, txg, EINVAL));
			}
			/* Fail if top level vdev is raidz */
			if (tvd->vdev_ops == &vdev_raidz_ops) {
				return (spa_vdev_exit(spa, vd, txg, EINVAL));
			}
			/*
			 * Need the top level mirror to be
			 * a mirror of leaf vdevs only
			 */
			if (tvd->vdev_ops == &vdev_mirror_ops) {
				for (uint64_t cid = 0;
				    cid < tvd->vdev_children; cid++) {
					vdev_t *cvd = tvd->vdev_child[cid];
					if (!cvd->vdev_ops->vdev_op_leaf) {
						return (spa_vdev_exit(spa, vd,
						    txg, EINVAL));
					}
				}
			}
		}
	}

	for (int c = 0; c < vd->vdev_children; c++) {

		/*
		 * Set the vdev id to the first hole, if one exists.
		 */
		for (id = 0; id < rvd->vdev_children; id++) {
			if (rvd->vdev_child[id]->vdev_ishole) {
				vdev_free(rvd->vdev_child[id]);
				break;
			}
		}
		tvd = vd->vdev_child[c];
		vdev_remove_child(vd, tvd);
		tvd->vdev_id = id;
		vdev_add_child(rvd, tvd);
		vdev_config_dirty(tvd);
	}

	if (nspares != 0) {
		spa_set_aux_vdevs(&spa->spa_spares, spares, nspares,
		    ZPOOL_CONFIG_SPARES);
		spa_load_spares(spa);
		spa->spa_spares.sav_sync = B_TRUE;
	}

	if (nl2cache != 0) {
		spa_set_aux_vdevs(&spa->spa_l2cache, l2cache, nl2cache,
		    ZPOOL_CONFIG_L2CACHE);
		spa_load_l2cache(spa);
		spa->spa_l2cache.sav_sync = B_TRUE;
	}

	/*
	 * We have to be careful when adding new vdevs to an existing pool.
	 * If other threads start allocating from these vdevs before we
	 * sync the config cache, and we lose power, then upon reboot we may
	 * fail to open the pool because there are DVAs that the config cache
	 * can't translate.  Therefore, we first add the vdevs without
	 * initializing metaslabs; sync the config cache (via spa_vdev_exit());
	 * and then let spa_config_update() initialize the new metaslabs.
	 *
	 * spa_load() checks for added-but-not-initialized vdevs, so that
	 * if we lose power at any point in this sequence, the remaining
	 * steps will be completed the next time we load the pool.
	 */
	(void) spa_vdev_exit(spa, vd, txg, 0);

	mutex_enter(&spa_namespace_lock);
	spa_config_update(spa, SPA_CONFIG_UPDATE_POOL);
	spa_event_notify(spa, NULL, NULL, ESC_ZFS_VDEV_ADD);
	mutex_exit(&spa_namespace_lock);

	return (0);
}