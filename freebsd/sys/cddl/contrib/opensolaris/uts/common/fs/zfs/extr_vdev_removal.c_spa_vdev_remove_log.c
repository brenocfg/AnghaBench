#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ vs_alloc; } ;
struct TYPE_13__ {int vdev_islog; char* vdev_path; scalar_t__ vdev_top_zap; scalar_t__ vdev_leaf_zap; int /*<<< orphan*/  vdev_config_dirty_node; int /*<<< orphan*/  vdev_state_dirty_node; int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  vdev_removing; TYPE_1__ vdev_stat; struct TYPE_13__* vdev_top; int /*<<< orphan*/ * vdev_spa; int /*<<< orphan*/ * vdev_mg; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sysevent_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_REMOVE_DEV ; 
 int /*<<< orphan*/  FTAG ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 scalar_t__ TXG_CONCURRENT_STATES ; 
 scalar_t__ TXG_DEFER_SIZE ; 
 int /*<<< orphan*/  VDD_DTL ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_CANCELED ; 
 int /*<<< orphan*/  VDEV_LABEL_REMOVE ; 
 scalar_t__ list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_group_passivate (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_event_create (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int spa_reset_logs (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_vdev_config_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_config_clean (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_config_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_dirty_leaves (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_remove_make_hole_and_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_state_clean (TYPE_2__*) ; 

__attribute__((used)) static int
spa_vdev_remove_log(vdev_t *vd, uint64_t *txg)
{
	metaslab_group_t *mg = vd->vdev_mg;
	spa_t *spa = vd->vdev_spa;
	int error = 0;

	ASSERT(vd->vdev_islog);
	ASSERT(vd == vd->vdev_top);

	/*
	 * Stop allocating from this vdev.
	 */
	metaslab_group_passivate(mg);

	/*
	 * Wait for the youngest allocations and frees to sync,
	 * and then wait for the deferral of those frees to finish.
	 */
	spa_vdev_config_exit(spa, NULL,
	    *txg + TXG_CONCURRENT_STATES + TXG_DEFER_SIZE, 0, FTAG);

	/*
	 * Evacuate the device.  We don't hold the config lock as writer
	 * since we need to do I/O but we do keep the
	 * spa_namespace_lock held.  Once this completes the device
	 * should no longer have any blocks allocated on it.
	 */
	if (vd->vdev_islog) {
		if (vd->vdev_stat.vs_alloc != 0)
			error = spa_reset_logs(spa);
	}

	*txg = spa_vdev_config_enter(spa);

	if (error != 0) {
		metaslab_group_activate(mg);
		return (error);
	}
	ASSERT0(vd->vdev_stat.vs_alloc);

	/*
	 * The evacuation succeeded.  Remove any remaining MOS metadata
	 * associated with this vdev, and wait for these changes to sync.
	 */
	vd->vdev_removing = B_TRUE;

	vdev_dirty_leaves(vd, VDD_DTL, *txg);
	vdev_config_dirty(vd);

	spa_history_log_internal(spa, "vdev remove", NULL,
	    "%s vdev %llu (log) %s", spa_name(spa), vd->vdev_id,
	    (vd->vdev_path != NULL) ? vd->vdev_path : "-");

	/* Make sure these changes are sync'ed */
	spa_vdev_config_exit(spa, NULL, *txg, 0, FTAG);

	/* Stop initializing */
	(void) vdev_initialize_stop_all(vd, VDEV_INITIALIZE_CANCELED);

	*txg = spa_vdev_config_enter(spa);

	sysevent_t *ev = spa_event_create(spa, vd, NULL,
	    ESC_ZFS_VDEV_REMOVE_DEV);
	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	/* The top ZAP should have been destroyed by vdev_remove_empty. */
	ASSERT0(vd->vdev_top_zap);
	/* The leaf ZAP should have been destroyed by vdev_dtl_sync. */
	ASSERT0(vd->vdev_leaf_zap);

	(void) vdev_label_init(vd, 0, VDEV_LABEL_REMOVE);

	if (list_link_active(&vd->vdev_state_dirty_node))
		vdev_state_clean(vd);
	if (list_link_active(&vd->vdev_config_dirty_node))
		vdev_config_clean(vd);

	/*
	 * Clean up the vdev namespace.
	 */
	vdev_remove_make_hole_and_free(vd);

	if (ev != NULL)
		spa_event_post(ev);

	return (0);
}