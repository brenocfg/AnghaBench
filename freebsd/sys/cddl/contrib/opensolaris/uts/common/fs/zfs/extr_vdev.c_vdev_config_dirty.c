#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int vdev_children; int /*<<< orphan*/  vdev_config_dirty_node; struct TYPE_12__* vdev_top; struct TYPE_12__** vdev_child; TYPE_3__* vdev_aux; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint_t ;
struct TYPE_13__ {int /*<<< orphan*/  spa_config_dirty_list; TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_14__ {int sav_count; scalar_t__ sav_sync; int /*<<< orphan*/  sav_config; TYPE_1__** sav_vdevs; } ;
typedef  TYPE_3__ spa_aux_vdev_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 scalar_t__ dsl_pool_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ spa_config_held (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (TYPE_2__*) ; 
 int spa_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/ * vdev_config_generate (TYPE_2__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_is_concrete (TYPE_1__*) ; 

void
vdev_config_dirty(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;
	vdev_t *rvd = spa->spa_root_vdev;
	int c;

	ASSERT(spa_writeable(spa));

	/*
	 * If this is an aux vdev (as with l2cache and spare devices), then we
	 * update the vdev config manually and set the sync flag.
	 */
	if (vd->vdev_aux != NULL) {
		spa_aux_vdev_t *sav = vd->vdev_aux;
		nvlist_t **aux;
		uint_t naux;

		for (c = 0; c < sav->sav_count; c++) {
			if (sav->sav_vdevs[c] == vd)
				break;
		}

		if (c == sav->sav_count) {
			/*
			 * We're being removed.  There's nothing more to do.
			 */
			ASSERT(sav->sav_sync == B_TRUE);
			return;
		}

		sav->sav_sync = B_TRUE;

		if (nvlist_lookup_nvlist_array(sav->sav_config,
		    ZPOOL_CONFIG_L2CACHE, &aux, &naux) != 0) {
			VERIFY(nvlist_lookup_nvlist_array(sav->sav_config,
			    ZPOOL_CONFIG_SPARES, &aux, &naux) == 0);
		}

		ASSERT(c < naux);

		/*
		 * Setting the nvlist in the middle if the array is a little
		 * sketchy, but it will work.
		 */
		nvlist_free(aux[c]);
		aux[c] = vdev_config_generate(spa, vd, B_TRUE, 0);

		return;
	}

	/*
	 * The dirty list is protected by the SCL_CONFIG lock.  The caller
	 * must either hold SCL_CONFIG as writer, or must be the sync thread
	 * (which holds SCL_CONFIG as reader).  There's only one sync thread,
	 * so this is sufficient to ensure mutual exclusion.
	 */
	ASSERT(spa_config_held(spa, SCL_CONFIG, RW_WRITER) ||
	    (dsl_pool_sync_context(spa_get_dsl(spa)) &&
	    spa_config_held(spa, SCL_CONFIG, RW_READER)));

	if (vd == rvd) {
		for (c = 0; c < rvd->vdev_children; c++)
			vdev_config_dirty(rvd->vdev_child[c]);
	} else {
		ASSERT(vd == vd->vdev_top);

		if (!list_link_active(&vd->vdev_config_dirty_node) &&
		    vdev_is_concrete(vd)) {
			list_insert_head(&spa->spa_config_dirty_list, vd);
		}
	}
}