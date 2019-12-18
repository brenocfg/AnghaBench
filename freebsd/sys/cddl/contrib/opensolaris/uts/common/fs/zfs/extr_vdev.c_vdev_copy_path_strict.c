#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ vdev_guid; scalar_t__ vdev_children; TYPE_2__* vdev_ops; struct TYPE_9__** vdev_child; scalar_t__ vdev_ishole; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_10__ {scalar_t__ vdev_op_leaf; int /*<<< orphan*/  vdev_op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_copy_path_impl (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_dbgmsg (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ vdev_indirect_ops ; 
 TYPE_2__ vdev_missing_ops ; 

int
vdev_copy_path_strict(vdev_t *svd, vdev_t *dvd)
{
	if ((svd->vdev_ops == &vdev_missing_ops) ||
	    (svd->vdev_ishole && dvd->vdev_ishole) ||
	    (dvd->vdev_ops == &vdev_indirect_ops))
		return (0);

	if (svd->vdev_ops != dvd->vdev_ops) {
		vdev_dbgmsg(svd, "vdev_copy_path: vdev type mismatch: %s != %s",
		    svd->vdev_ops->vdev_op_type, dvd->vdev_ops->vdev_op_type);
		return (SET_ERROR(EINVAL));
	}

	if (svd->vdev_guid != dvd->vdev_guid) {
		vdev_dbgmsg(svd, "vdev_copy_path: guids mismatch (%llu != "
		    "%llu)", (u_longlong_t)svd->vdev_guid,
		    (u_longlong_t)dvd->vdev_guid);
		return (SET_ERROR(EINVAL));
	}

	if (svd->vdev_children != dvd->vdev_children) {
		vdev_dbgmsg(svd, "vdev_copy_path: children count mismatch: "
		    "%llu != %llu", (u_longlong_t)svd->vdev_children,
		    (u_longlong_t)dvd->vdev_children);
		return (SET_ERROR(EINVAL));
	}

	for (uint64_t i = 0; i < svd->vdev_children; i++) {
		int error = vdev_copy_path_strict(svd->vdev_child[i],
		    dvd->vdev_child[i]);
		if (error != 0)
			return (error);
	}

	if (svd->vdev_ops->vdev_op_leaf)
		vdev_copy_path_impl(svd, dvd);

	return (0);
}