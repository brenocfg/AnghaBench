#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zio_priority_t ;
struct TYPE_7__ {int /*<<< orphan*/  vq_lock; int /*<<< orphan*/  vq_active_tree; } ;
struct TYPE_6__ {TYPE_2__ vdev_queue; } ;
typedef  TYPE_1__ vdev_t ;
typedef  TYPE_2__ vdev_queue_t ;

/* Variables and functions */
 scalar_t__ ZIO_PRIORITY_NUM_QUEUEABLE ; 
 int /*<<< orphan*/  ZIO_TYPE_READ ; 
 int /*<<< orphan*/  ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vdev_queue_class_tree (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * vdev_queue_type_tree (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
vdev_queue_fini(vdev_t *vd)
{
	vdev_queue_t *vq = &vd->vdev_queue;

	for (zio_priority_t p = 0; p < ZIO_PRIORITY_NUM_QUEUEABLE; p++)
		avl_destroy(vdev_queue_class_tree(vq, p));
	avl_destroy(&vq->vq_active_tree);
	avl_destroy(vdev_queue_type_tree(vq, ZIO_TYPE_READ));
	avl_destroy(vdev_queue_type_tree(vq, ZIO_TYPE_WRITE));

	mutex_destroy(&vq->vq_lock);
}