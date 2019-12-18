#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zio_priority_t ;
struct TYPE_8__ {TYPE_1__* vq_class; int /*<<< orphan*/  vq_active_tree; int /*<<< orphan*/  vq_lock; TYPE_2__* vq_vdev; } ;
typedef  TYPE_3__ vdev_queue_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {int /*<<< orphan*/ * vdev_spa; } ;
struct TYPE_6__ {scalar_t__ vqc_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 size_t ZIO_PRIORITY_NUM_QUEUEABLE ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_queue_class_max_active (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ vdev_queue_class_min_active (size_t) ; 
 int /*<<< orphan*/ * vdev_queue_class_tree (TYPE_3__*,size_t) ; 
 scalar_t__ zfs_vdev_max_active ; 

__attribute__((used)) static zio_priority_t
vdev_queue_class_to_issue(vdev_queue_t *vq)
{
	spa_t *spa = vq->vq_vdev->vdev_spa;
	zio_priority_t p;

	ASSERT(MUTEX_HELD(&vq->vq_lock));

	if (avl_numnodes(&vq->vq_active_tree) >= zfs_vdev_max_active)
		return (ZIO_PRIORITY_NUM_QUEUEABLE);

	/* find a queue that has not reached its minimum # outstanding i/os */
	for (p = 0; p < ZIO_PRIORITY_NUM_QUEUEABLE; p++) {
		if (avl_numnodes(vdev_queue_class_tree(vq, p)) > 0 &&
		    vq->vq_class[p].vqc_active <
		    vdev_queue_class_min_active(p))
			return (p);
	}

	/*
	 * If we haven't found a queue, look for one that hasn't reached its
	 * maximum # outstanding i/os.
	 */
	for (p = 0; p < ZIO_PRIORITY_NUM_QUEUEABLE; p++) {
		if (avl_numnodes(vdev_queue_class_tree(vq, p)) > 0 &&
		    vq->vq_class[p].vqc_active <
		    vdev_queue_class_max_active(spa, p))
			return (p);
	}

	/* No eligible queued i/os */
	return (ZIO_PRIORITY_NUM_QUEUEABLE);
}