#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_4__** sav_vdevs; } ;
struct TYPE_20__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_4__** sav_vdevs; } ;
struct TYPE_22__ {int /*<<< orphan*/ * spa_comment; void* spa_indirect_vdevs_loaded; scalar_t__ spa_async_suspended; TYPE_2__ spa_l2cache; TYPE_1__ spa_spares; int /*<<< orphan*/ * spa_meta_objset; int /*<<< orphan*/ * spa_dsl_pool; TYPE_4__* spa_root_vdev; int /*<<< orphan*/  spa_deferred_bpobj; int /*<<< orphan*/ * spa_checkpoint_discard_zthr; int /*<<< orphan*/ * spa_condense_zthr; int /*<<< orphan*/ * spa_vdev_removal; TYPE_4__** spa_async_zio_root; void* spa_sync_on; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_23__ {int vdev_children; int /*<<< orphan*/ * vdev_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_ACTIVE ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_unload (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_pool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__**,int) ; 
 int max_ncpus ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_condense_fini (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  spa_l2cache_drop (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_removal_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim_thread_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  txg_sync_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_clear_stats (TYPE_4__*) ; 
 int /*<<< orphan*/  vdev_free (TYPE_4__*) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_metaslab_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (TYPE_4__*) ; 
 int /*<<< orphan*/  zthr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_unload(spa_t *spa)
{
	int i;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	spa_load_note(spa, "UNLOADING");

	/*
	 * Stop TRIM thread.
	 */
	trim_thread_destroy(spa);

	/*
	 * Stop async tasks.
	 */
	spa_async_suspend(spa);

	if (spa->spa_root_vdev) {
		vdev_initialize_stop_all(spa->spa_root_vdev,
		    VDEV_INITIALIZE_ACTIVE);
	}

	/*
	 * Stop syncing.
	 */
	if (spa->spa_sync_on) {
		txg_sync_stop(spa->spa_dsl_pool);
		spa->spa_sync_on = B_FALSE;
	}

	/*
	 * Even though vdev_free() also calls vdev_metaslab_fini, we need
	 * to call it earlier, before we wait for async i/o to complete.
	 * This ensures that there is no async metaslab prefetching, by
	 * calling taskq_wait(mg_taskq).
	 */
	if (spa->spa_root_vdev != NULL) {
		spa_config_enter(spa, SCL_ALL, spa, RW_WRITER);
		for (int c = 0; c < spa->spa_root_vdev->vdev_children; c++)
			vdev_metaslab_fini(spa->spa_root_vdev->vdev_child[c]);
		spa_config_exit(spa, SCL_ALL, spa);
	}

	/*
	 * Wait for any outstanding async I/O to complete.
	 */
	if (spa->spa_async_zio_root != NULL) {
		for (int i = 0; i < max_ncpus; i++)
			(void) zio_wait(spa->spa_async_zio_root[i]);
		kmem_free(spa->spa_async_zio_root, max_ncpus * sizeof (void *));
		spa->spa_async_zio_root = NULL;
	}

	if (spa->spa_vdev_removal != NULL) {
		spa_vdev_removal_destroy(spa->spa_vdev_removal);
		spa->spa_vdev_removal = NULL;
	}

	if (spa->spa_condense_zthr != NULL) {
		zthr_destroy(spa->spa_condense_zthr);
		spa->spa_condense_zthr = NULL;
	}

	if (spa->spa_checkpoint_discard_zthr != NULL) {
		zthr_destroy(spa->spa_checkpoint_discard_zthr);
		spa->spa_checkpoint_discard_zthr = NULL;
	}

	spa_condense_fini(spa);

	bpobj_close(&spa->spa_deferred_bpobj);

	spa_config_enter(spa, SCL_ALL, spa, RW_WRITER);

	/*
	 * Close all vdevs.
	 */
	if (spa->spa_root_vdev)
		vdev_free(spa->spa_root_vdev);
	ASSERT(spa->spa_root_vdev == NULL);

	/*
	 * Close the dsl pool.
	 */
	if (spa->spa_dsl_pool) {
		dsl_pool_close(spa->spa_dsl_pool);
		spa->spa_dsl_pool = NULL;
		spa->spa_meta_objset = NULL;
	}

	ddt_unload(spa);

	/*
	 * Drop and purge level 2 cache
	 */
	spa_l2cache_drop(spa);

	for (i = 0; i < spa->spa_spares.sav_count; i++)
		vdev_free(spa->spa_spares.sav_vdevs[i]);
	if (spa->spa_spares.sav_vdevs) {
		kmem_free(spa->spa_spares.sav_vdevs,
		    spa->spa_spares.sav_count * sizeof (void *));
		spa->spa_spares.sav_vdevs = NULL;
	}
	if (spa->spa_spares.sav_config) {
		nvlist_free(spa->spa_spares.sav_config);
		spa->spa_spares.sav_config = NULL;
	}
	spa->spa_spares.sav_count = 0;

	for (i = 0; i < spa->spa_l2cache.sav_count; i++) {
		vdev_clear_stats(spa->spa_l2cache.sav_vdevs[i]);
		vdev_free(spa->spa_l2cache.sav_vdevs[i]);
	}
	if (spa->spa_l2cache.sav_vdevs) {
		kmem_free(spa->spa_l2cache.sav_vdevs,
		    spa->spa_l2cache.sav_count * sizeof (void *));
		spa->spa_l2cache.sav_vdevs = NULL;
	}
	if (spa->spa_l2cache.sav_config) {
		nvlist_free(spa->spa_l2cache.sav_config);
		spa->spa_l2cache.sav_config = NULL;
	}
	spa->spa_l2cache.sav_count = 0;

	spa->spa_async_suspended = 0;

	spa->spa_indirect_vdevs_loaded = B_FALSE;

	if (spa->spa_comment != NULL) {
		spa_strfree(spa->spa_comment);
		spa->spa_comment = NULL;
	}

	spa_config_exit(spa, SCL_ALL, spa);
}