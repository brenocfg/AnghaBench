#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  vs_scan_removing; scalar_t__* vs_bytes; scalar_t__* vs_ops; int /*<<< orphan*/  vs_fragmentation; int /*<<< orphan*/  vs_physical_ashift; int /*<<< orphan*/  vs_logical_ashift; int /*<<< orphan*/  vs_configured_ashift; int /*<<< orphan*/  vs_esize; int /*<<< orphan*/  vs_initialize_action_time; int /*<<< orphan*/  vs_initialize_state; int /*<<< orphan*/  vs_initialize_bytes_est; int /*<<< orphan*/  vs_initialize_bytes_done; int /*<<< orphan*/  vs_rsize; int /*<<< orphan*/  vs_state; scalar_t__ vs_timestamp; } ;
struct TYPE_15__ {scalar_t__ vdev_max_asize; scalar_t__ vdev_asize; unsigned long long vdev_ms_shift; int vdev_children; int /*<<< orphan*/  vdev_stat_lock; int /*<<< orphan*/  vdev_removing; TYPE_4__ vdev_stat; struct TYPE_15__** vdev_child; TYPE_2__* vdev_mg; struct TYPE_15__* vdev_top; int /*<<< orphan*/ * vdev_aux; int /*<<< orphan*/  vdev_physical_ashift; int /*<<< orphan*/  vdev_logical_ashift; int /*<<< orphan*/  vdev_ashift; int /*<<< orphan*/  vdev_initialize_action_time; int /*<<< orphan*/  vdev_initialize_state; int /*<<< orphan*/  vdev_initialize_bytes_est; int /*<<< orphan*/  vdev_initialize_bytes_done; TYPE_1__* vdev_ops; int /*<<< orphan*/  vdev_state; TYPE_5__* vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  TYPE_4__ vdev_stat_t ;
struct TYPE_17__ {scalar_t__ spa_bootsize; TYPE_3__* spa_root_vdev; } ;
typedef  TYPE_5__ spa_t ;
struct TYPE_14__ {int /*<<< orphan*/  mg_fragmentation; } ;
struct TYPE_13__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  P2ALIGN (scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ VDEV_LABEL_END_SIZE ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 int ZIO_TYPES ; 
 int /*<<< orphan*/  bcopy (TYPE_4__*,TYPE_4__*,int) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_config_held (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_get_min_asize (TYPE_3__*) ; 
 scalar_t__ vdev_is_concrete (TYPE_3__*) ; 

void
vdev_get_stats(vdev_t *vd, vdev_stat_t *vs)
{
	spa_t *spa = vd->vdev_spa;
	vdev_t *rvd = spa->spa_root_vdev;
	vdev_t *tvd = vd->vdev_top;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_READER) != 0);

	mutex_enter(&vd->vdev_stat_lock);
	bcopy(&vd->vdev_stat, vs, sizeof (*vs));
	vs->vs_timestamp = gethrtime() - vs->vs_timestamp;
	vs->vs_state = vd->vdev_state;
	vs->vs_rsize = vdev_get_min_asize(vd);
	if (vd->vdev_ops->vdev_op_leaf) {
		vs->vs_rsize += VDEV_LABEL_START_SIZE + VDEV_LABEL_END_SIZE;
		/*
		 * Report intializing progress. Since we don't have the
		 * initializing locks held, this is only an estimate (although a
		 * fairly accurate one).
		 */
		vs->vs_initialize_bytes_done = vd->vdev_initialize_bytes_done;
		vs->vs_initialize_bytes_est = vd->vdev_initialize_bytes_est;
		vs->vs_initialize_state = vd->vdev_initialize_state;
		vs->vs_initialize_action_time = vd->vdev_initialize_action_time;
	}
	/*
	 * Report expandable space on top-level, non-auxillary devices only.
	 * The expandable space is reported in terms of metaslab sized units
	 * since that determines how much space the pool can expand.
	 */
	if (vd->vdev_aux == NULL && tvd != NULL && vd->vdev_max_asize != 0) {
		vs->vs_esize = P2ALIGN(vd->vdev_max_asize - vd->vdev_asize -
		    spa->spa_bootsize, 1ULL << tvd->vdev_ms_shift);
	}
	vs->vs_configured_ashift = vd->vdev_top != NULL
	    ? vd->vdev_top->vdev_ashift : vd->vdev_ashift;
	vs->vs_logical_ashift = vd->vdev_logical_ashift;
	vs->vs_physical_ashift = vd->vdev_physical_ashift;
	if (vd->vdev_aux == NULL && vd == vd->vdev_top &&
	    vdev_is_concrete(vd)) {
		vs->vs_fragmentation = vd->vdev_mg->mg_fragmentation;
	}

	/*
	 * If we're getting stats on the root vdev, aggregate the I/O counts
	 * over all top-level vdevs (i.e. the direct children of the root).
	 */
	if (vd == rvd) {
		for (int c = 0; c < rvd->vdev_children; c++) {
			vdev_t *cvd = rvd->vdev_child[c];
			vdev_stat_t *cvs = &cvd->vdev_stat;

			for (int t = 0; t < ZIO_TYPES; t++) {
				vs->vs_ops[t] += cvs->vs_ops[t];
				vs->vs_bytes[t] += cvs->vs_bytes[t];
			}
			cvs->vs_scan_removing = cvd->vdev_removing;
		}
	}
	mutex_exit(&vd->vdev_stat_lock);
}