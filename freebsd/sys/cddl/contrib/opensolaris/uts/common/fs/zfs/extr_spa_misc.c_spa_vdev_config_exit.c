#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  vdev_initialize_lock; TYPE_1__* vdev_ops; int /*<<< orphan*/ * vdev_dtl_sm; int /*<<< orphan*/  vdev_detached; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_19__ {int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_config_generation; int /*<<< orphan*/  spa_config_dirty_list; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/ * spa_pending_vdev; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_17__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_CANCELED ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ metaslab_class_validate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ spa_last_synced_txg (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_log_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_write_cachefile (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdev_dtl_reassess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_initialize_stop (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_handle_panic_injection (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_injection_enabled ; 

void
spa_vdev_config_exit(spa_t *spa, vdev_t *vd, uint64_t txg, int error, char *tag)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	int config_changed = B_FALSE;

	ASSERT(txg > spa_last_synced_txg(spa));

	spa->spa_pending_vdev = NULL;

	/*
	 * Reassess the DTLs.
	 */
	vdev_dtl_reassess(spa->spa_root_vdev, 0, 0, B_FALSE);

	if (error == 0 && !list_is_empty(&spa->spa_config_dirty_list)) {
		config_changed = B_TRUE;
		spa->spa_config_generation++;
	}

	/*
	 * Verify the metaslab classes.
	 */
	ASSERT(metaslab_class_validate(spa_normal_class(spa)) == 0);
	ASSERT(metaslab_class_validate(spa_log_class(spa)) == 0);

	spa_config_exit(spa, SCL_ALL, spa);

	/*
	 * Panic the system if the specified tag requires it.  This
	 * is useful for ensuring that configurations are updated
	 * transactionally.
	 */
	if (zio_injection_enabled)
		zio_handle_panic_injection(spa, tag, 0);

	/*
	 * Note: this txg_wait_synced() is important because it ensures
	 * that there won't be more than one config change per txg.
	 * This allows us to use the txg as the generation number.
	 */
	if (error == 0)
		txg_wait_synced(spa->spa_dsl_pool, txg);

	if (vd != NULL) {
		ASSERT(!vd->vdev_detached || vd->vdev_dtl_sm == NULL);
		if (vd->vdev_ops->vdev_op_leaf) {
			mutex_enter(&vd->vdev_initialize_lock);
			vdev_initialize_stop(vd, VDEV_INITIALIZE_CANCELED);
			mutex_exit(&vd->vdev_initialize_lock);
		}

		spa_config_enter(spa, SCL_ALL, spa, RW_WRITER);
		vdev_free(vd);
		spa_config_exit(spa, SCL_ALL, spa);
	}

	/*
	 * If the config changed, update the config cache.
	 */
	if (config_changed)
		spa_write_cachefile(spa, B_FALSE, B_TRUE);
}