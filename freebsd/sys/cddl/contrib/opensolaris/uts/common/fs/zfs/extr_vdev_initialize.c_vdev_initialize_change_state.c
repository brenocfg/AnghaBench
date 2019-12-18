#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_initialize_state; int /*<<< orphan*/  vdev_path; int /*<<< orphan*/  vdev_initialize_action_time; int /*<<< orphan*/  vdev_guid; int /*<<< orphan*/ * vdev_spa; int /*<<< orphan*/  vdev_initialize_lock; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int vdev_initializing_state_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_mos_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
#define  VDEV_INITIALIZE_ACTIVE 131 
#define  VDEV_INITIALIZE_CANCELED 130 
#define  VDEV_INITIALIZE_COMPLETE 129 
#define  VDEV_INITIALIZE_SUSPENDED 128 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_dd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,unsigned long long) ; 
 TYPE_3__* spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize_zap_update_sync ; 

__attribute__((used)) static void
vdev_initialize_change_state(vdev_t *vd, vdev_initializing_state_t new_state)
{
	ASSERT(MUTEX_HELD(&vd->vdev_initialize_lock));
	spa_t *spa = vd->vdev_spa;

	if (new_state == vd->vdev_initialize_state)
		return;

	/*
	 * Copy the vd's guid, this will be freed by the sync task.
	 */
	uint64_t *guid = kmem_zalloc(sizeof (uint64_t), KM_SLEEP);
	*guid = vd->vdev_guid;

	/*
	 * If we're suspending, then preserving the original start time.
	 */
	if (vd->vdev_initialize_state != VDEV_INITIALIZE_SUSPENDED) {
		vd->vdev_initialize_action_time = gethrestime_sec();
	}
	vd->vdev_initialize_state = new_state;

	dmu_tx_t *tx = dmu_tx_create_dd(spa_get_dsl(spa)->dp_mos_dir);
	VERIFY0(dmu_tx_assign(tx, TXG_WAIT));
	dsl_sync_task_nowait(spa_get_dsl(spa), vdev_initialize_zap_update_sync,
	    guid, 2, ZFS_SPACE_CHECK_RESERVED, tx);

	switch (new_state) {
	case VDEV_INITIALIZE_ACTIVE:
		spa_history_log_internal(spa, "initialize", tx,
		    "vdev=%s activated", vd->vdev_path);
		break;
	case VDEV_INITIALIZE_SUSPENDED:
		spa_history_log_internal(spa, "initialize", tx,
		    "vdev=%s suspended", vd->vdev_path);
		break;
	case VDEV_INITIALIZE_CANCELED:
		spa_history_log_internal(spa, "initialize", tx,
		    "vdev=%s canceled", vd->vdev_path);
		break;
	case VDEV_INITIALIZE_COMPLETE:
		spa_history_log_internal(spa, "initialize", tx,
		    "vdev=%s complete", vd->vdev_path);
		break;
	default:
		panic("invalid state %llu", (unsigned long long)new_state);
	}

	dmu_tx_commit(tx);
}