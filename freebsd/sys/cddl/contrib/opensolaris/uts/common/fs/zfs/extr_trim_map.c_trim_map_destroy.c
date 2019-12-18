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
struct TYPE_13__ {TYPE_3__* vdev_trimmap; int /*<<< orphan*/  vdev_spa; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_14__ {int /*<<< orphan*/  tm_lock; int /*<<< orphan*/  tm_head; int /*<<< orphan*/  tm_pending_writes; int /*<<< orphan*/  tm_inflight_writes; int /*<<< orphan*/  tm_inflight_frees; int /*<<< orphan*/  tm_queued_frees; } ;
typedef  TYPE_3__ trim_seg_t ;
typedef  TYPE_3__ trim_map_t ;
struct TYPE_12__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIM_MAP_REM (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim_map_vdev_commit_done (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_trim_enabled ; 

void
trim_map_destroy(vdev_t *vd)
{
	trim_map_t *tm;
	trim_seg_t *ts;

	ASSERT(vd->vdev_ops->vdev_op_leaf);

	if (!zfs_trim_enabled)
		return;

	tm = vd->vdev_trimmap;
	if (tm == NULL)
		return;

	/*
	 * We may have been called before trim_map_vdev_commit_done()
	 * had a chance to run, so do it now to prune the remaining
	 * inflight frees.
	 */
	trim_map_vdev_commit_done(vd->vdev_spa, vd);

	mutex_enter(&tm->tm_lock);
	while ((ts = list_head(&tm->tm_head)) != NULL) {
		avl_remove(&tm->tm_queued_frees, ts);
		TRIM_MAP_REM(tm, ts);
		kmem_free(ts, sizeof (*ts));
	}
	mutex_exit(&tm->tm_lock);

	avl_destroy(&tm->tm_queued_frees);
	avl_destroy(&tm->tm_inflight_frees);
	avl_destroy(&tm->tm_inflight_writes);
	list_destroy(&tm->tm_pending_writes);
	list_destroy(&tm->tm_head);
	mutex_destroy(&tm->tm_lock);
	kmem_free(tm, sizeof (*tm));
	vd->vdev_trimmap = NULL;
}