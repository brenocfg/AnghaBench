#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zio_priority_t ;
struct TYPE_5__ {TYPE_1__* vq_class; } ;
typedef  TYPE_2__ vdev_queue_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
struct TYPE_4__ {int /*<<< orphan*/  vqc_queued_tree; } ;

/* Variables and functions */

__attribute__((used)) static inline avl_tree_t *
vdev_queue_class_tree(vdev_queue_t *vq, zio_priority_t p)
{
	return (&vq->vq_class[p].vqc_queued_tree);
}