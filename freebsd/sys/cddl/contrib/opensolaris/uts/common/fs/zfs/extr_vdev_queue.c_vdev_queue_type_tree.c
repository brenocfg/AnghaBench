#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zio_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  vq_write_offset_tree; int /*<<< orphan*/  vq_read_offset_tree; } ;
typedef  TYPE_1__ vdev_queue_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 

__attribute__((used)) static inline avl_tree_t *
vdev_queue_type_tree(vdev_queue_t *vq, zio_type_t t)
{
	if (t == ZIO_TYPE_READ)
		return (&vq->vq_read_offset_tree);
	else if (t == ZIO_TYPE_WRITE)
		return (&vq->vq_write_offset_tree);
	else
		return (NULL);
}