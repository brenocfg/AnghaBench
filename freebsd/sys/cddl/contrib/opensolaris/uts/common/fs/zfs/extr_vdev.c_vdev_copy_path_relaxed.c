#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vdev_child; int /*<<< orphan*/ * vdev_ops; int /*<<< orphan*/  vdev_children; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_copy_path_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_root_ops ; 

void
vdev_copy_path_relaxed(vdev_t *srvd, vdev_t *drvd)
{
	uint64_t children = MIN(srvd->vdev_children, drvd->vdev_children);
	ASSERT(srvd->vdev_ops == &vdev_root_ops);
	ASSERT(drvd->vdev_ops == &vdev_root_ops);

	for (uint64_t i = 0; i < children; i++) {
		vdev_copy_path_search(srvd->vdev_child[i],
		    drvd->vdev_child[i]);
	}
}