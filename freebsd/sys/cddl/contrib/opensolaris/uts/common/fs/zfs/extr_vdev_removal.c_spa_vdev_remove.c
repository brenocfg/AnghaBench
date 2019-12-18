#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ vdev_islog; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sysevent_t ;
struct TYPE_22__ {void* sav_sync; int /*<<< orphan*/  sav_config; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_21__ {void* sav_sync; int /*<<< orphan*/  sav_config; int /*<<< orphan*/ * sav_vdevs; } ;
struct TYPE_24__ {TYPE_2__ spa_l2cache; TYPE_1__ spa_spares; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_REMOVE_AUX ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  VDEV_TYPE_L2CACHE ; 
 int /*<<< orphan*/  VDEV_TYPE_SPARE ; 
 int ZFS_ERR_CHECKPOINT_EXISTS ; 
 int ZFS_ERR_DISCARDING_CHECKPOINT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spa_event_create (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_discard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_event_post (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_active (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_has_checkpoint (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_4__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spa_load_l2cache (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_load_spares (TYPE_4__*) ; 
 TYPE_3__* spa_lookup_by_guid (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spa_name (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/ * spa_nvlist_lookup_by_guid (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_enter (TYPE_4__*) ; 
 int spa_vdev_exit (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spa_vdev_remove_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spa_vdev_remove_log (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int spa_vdev_remove_top (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int spa_writeable (TYPE_4__*) ; 

int
spa_vdev_remove(spa_t *spa, uint64_t guid, boolean_t unspare)
{
	vdev_t *vd;
	nvlist_t **spares, **l2cache, *nv;
	uint64_t txg = 0;
	uint_t nspares, nl2cache;
	int error = 0;
	boolean_t locked = MUTEX_HELD(&spa_namespace_lock);
	sysevent_t *ev = NULL;

	ASSERT(spa_writeable(spa));

	if (!locked)
		txg = spa_vdev_enter(spa);

	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	if (spa_feature_is_active(spa, SPA_FEATURE_POOL_CHECKPOINT)) {
		error = (spa_has_checkpoint(spa)) ?
		    ZFS_ERR_CHECKPOINT_EXISTS : ZFS_ERR_DISCARDING_CHECKPOINT;

		if (!locked)
			return (spa_vdev_exit(spa, NULL, txg, error));

		return (error);
	}

	vd = spa_lookup_by_guid(spa, guid, B_FALSE);

	if (spa->spa_spares.sav_vdevs != NULL &&
	    nvlist_lookup_nvlist_array(spa->spa_spares.sav_config,
	    ZPOOL_CONFIG_SPARES, &spares, &nspares) == 0 &&
	    (nv = spa_nvlist_lookup_by_guid(spares, nspares, guid)) != NULL) {
		/*
		 * Only remove the hot spare if it's not currently in use
		 * in this pool.
		 */
		if (vd == NULL || unspare) {
			char *nvstr = fnvlist_lookup_string(nv,
			    ZPOOL_CONFIG_PATH);
			spa_history_log_internal(spa, "vdev remove", NULL,
			    "%s vdev (%s) %s", spa_name(spa),
			    VDEV_TYPE_SPARE, nvstr);
			if (vd == NULL)
				vd = spa_lookup_by_guid(spa, guid, B_TRUE);
			ev = spa_event_create(spa, vd, NULL,
			    ESC_ZFS_VDEV_REMOVE_AUX);
			spa_vdev_remove_aux(spa->spa_spares.sav_config,
			    ZPOOL_CONFIG_SPARES, spares, nspares, nv);
			spa_load_spares(spa);
			spa->spa_spares.sav_sync = B_TRUE;
		} else {
			error = SET_ERROR(EBUSY);
		}
	} else if (spa->spa_l2cache.sav_vdevs != NULL &&
	    nvlist_lookup_nvlist_array(spa->spa_l2cache.sav_config,
	    ZPOOL_CONFIG_L2CACHE, &l2cache, &nl2cache) == 0 &&
	    (nv = spa_nvlist_lookup_by_guid(l2cache, nl2cache, guid)) != NULL) {
		char *nvstr = fnvlist_lookup_string(nv, ZPOOL_CONFIG_PATH);
		spa_history_log_internal(spa, "vdev remove", NULL,
		    "%s vdev (%s) %s", spa_name(spa), VDEV_TYPE_L2CACHE, nvstr);
		/*
		 * Cache devices can always be removed.
		 */
		vd = spa_lookup_by_guid(spa, guid, B_TRUE);
		ev = spa_event_create(spa, vd, NULL, ESC_ZFS_VDEV_REMOVE_AUX);
		spa_vdev_remove_aux(spa->spa_l2cache.sav_config,
		    ZPOOL_CONFIG_L2CACHE, l2cache, nl2cache, nv);
		spa_load_l2cache(spa);
		spa->spa_l2cache.sav_sync = B_TRUE;
	} else if (vd != NULL && vd->vdev_islog) {
		ASSERT(!locked);
		error = spa_vdev_remove_log(vd, &txg);
	} else if (vd != NULL) {
		ASSERT(!locked);
		error = spa_vdev_remove_top(vd, &txg);
	} else {
		/*
		 * There is no vdev of any kind with the specified guid.
		 */
		error = SET_ERROR(ENOENT);
	}

	if (!locked)
		error = spa_vdev_exit(spa, NULL, txg, error);

	if (ev != NULL) {
		if (error != 0) {
			spa_event_discard(ev);
		} else {
			spa_event_post(ev);
		}
	}

	return (error);
}