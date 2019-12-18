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
struct TYPE_6__ {int vdev_children; struct TYPE_6__** vdev_child; TYPE_1__* vdev_ops; scalar_t__ vdev_isl2cache; scalar_t__ vdev_isspare; scalar_t__ vdev_islog; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_5__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_readable (TYPE_2__*) ; 

__attribute__((used)) static uint64_t
dsl_scan_count_leaves(vdev_t *vd)
{
	uint64_t i, leaves = 0;
	
	/* we only count leaves that belong to the main pool and are readable */
	if (vd->vdev_islog || vd->vdev_isspare ||
	    vd->vdev_isl2cache || !vdev_readable(vd))
		return (0);
	
	if (vd->vdev_ops->vdev_op_leaf)
		return (1);
	
	for (i = 0; i < vd->vdev_children; i++) {
		leaves += dsl_scan_count_leaves(vd->vdev_child[i]);
	}
	
	return (leaves);
}