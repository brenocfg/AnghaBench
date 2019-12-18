#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vdev_children; int /*<<< orphan*/  vdev_top; TYPE_1__* vdev_ops; struct TYPE_6__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_dirty (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

void
vdev_dirty_leaves(vdev_t *vd, int flags, uint64_t txg)
{
	for (int c = 0; c < vd->vdev_children; c++)
		vdev_dirty_leaves(vd->vdev_child[c], flags, txg);

	if (vd->vdev_ops->vdev_op_leaf)
		vdev_dirty(vd->vdev_top, flags, vd, txg);
}