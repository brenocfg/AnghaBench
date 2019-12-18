#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t vdev_children; TYPE_2__** vdev_child; TYPE_1__* vdev_ops; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ vdev_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ VDEV_STATE_OFFLINE ; 

boolean_t
vdev_children_are_offline(vdev_t *vd)
{
	ASSERT(!vd->vdev_ops->vdev_op_leaf);

	for (uint64_t i = 0; i < vd->vdev_children; i++) {
		if (vd->vdev_child[i]->vdev_state != VDEV_STATE_OFFLINE)
			return (B_FALSE);
	}

	return (B_TRUE);
}