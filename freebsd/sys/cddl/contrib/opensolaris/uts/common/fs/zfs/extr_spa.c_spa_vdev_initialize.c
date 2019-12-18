#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ vdev_initialize_state; int /*<<< orphan*/  vdev_initialize_lock; TYPE_2__* vdev_top; int /*<<< orphan*/ * vdev_initialize_thread; TYPE_1__* vdev_ops; scalar_t__ vdev_detached; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_17__ {int /*<<< orphan*/  spa_dsl_pool; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_15__ {scalar_t__ vdev_removing; } ;
struct TYPE_14__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
#define  POOL_INITIALIZE_CANCEL 130 
#define  POOL_INITIALIZE_DO 129 
#define  POOL_INITIALIZE_SUSPEND 128 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDEV_INITIALIZE_ACTIVE ; 
 scalar_t__ VDEV_INITIALIZE_CANCELED ; 
 scalar_t__ VDEV_INITIALIZE_SUSPENDED ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned long long) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* spa_lookup_by_guid (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_initialize_stop (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_3__*) ; 

int
spa_vdev_initialize(spa_t *spa, uint64_t guid, uint64_t cmd_type)
{
	/*
	 * We hold the namespace lock through the whole function
	 * to prevent any changes to the pool while we're starting or
	 * stopping initialization. The config and state locks are held so that
	 * we can properly assess the vdev state before we commit to
	 * the initializing operation.
	 */
	mutex_enter(&spa_namespace_lock);
	spa_config_enter(spa, SCL_CONFIG | SCL_STATE, FTAG, RW_READER);

	/* Look up vdev and ensure it's a leaf. */
	vdev_t *vd = spa_lookup_by_guid(spa, guid, B_FALSE);
	if (vd == NULL || vd->vdev_detached) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(ENODEV));
	} else if (!vd->vdev_ops->vdev_op_leaf || !vdev_is_concrete(vd)) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(EINVAL));
	} else if (!vdev_writeable(vd)) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(EROFS));
	}
	mutex_enter(&vd->vdev_initialize_lock);
	spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);

	/*
	 * When we activate an initialize action we check to see
	 * if the vdev_initialize_thread is NULL. We do this instead
	 * of using the vdev_initialize_state since there might be
	 * a previous initialization process which has completed but
	 * the thread is not exited.
	 */
	if (cmd_type == POOL_INITIALIZE_DO &&
	    (vd->vdev_initialize_thread != NULL ||
	    vd->vdev_top->vdev_removing)) {
		mutex_exit(&vd->vdev_initialize_lock);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(EBUSY));
	} else if (cmd_type == POOL_INITIALIZE_CANCEL &&
	    (vd->vdev_initialize_state != VDEV_INITIALIZE_ACTIVE &&
	    vd->vdev_initialize_state != VDEV_INITIALIZE_SUSPENDED)) {
		mutex_exit(&vd->vdev_initialize_lock);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(ESRCH));
	} else if (cmd_type == POOL_INITIALIZE_SUSPEND &&
	    vd->vdev_initialize_state != VDEV_INITIALIZE_ACTIVE) {
		mutex_exit(&vd->vdev_initialize_lock);
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(ESRCH));
	}

	switch (cmd_type) {
	case POOL_INITIALIZE_DO:
		vdev_initialize(vd);
		break;
	case POOL_INITIALIZE_CANCEL:
		vdev_initialize_stop(vd, VDEV_INITIALIZE_CANCELED);
		break;
	case POOL_INITIALIZE_SUSPEND:
		vdev_initialize_stop(vd, VDEV_INITIALIZE_SUSPENDED);
		break;
	default:
		panic("invalid cmd_type %llu", (unsigned long long)cmd_type);
	}
	mutex_exit(&vd->vdev_initialize_lock);

	/* Sync out the initializing state */
	txg_wait_synced(spa->spa_dsl_pool, 0);
	mutex_exit(&spa_namespace_lock);

	return (0);
}