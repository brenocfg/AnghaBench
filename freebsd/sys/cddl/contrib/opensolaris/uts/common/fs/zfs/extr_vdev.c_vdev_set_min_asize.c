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
struct TYPE_4__ {int vdev_children; struct TYPE_4__** vdev_child; int /*<<< orphan*/  vdev_min_asize; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_get_min_asize (TYPE_1__*) ; 

void
vdev_set_min_asize(vdev_t *vd)
{
	vd->vdev_min_asize = vdev_get_min_asize(vd);

	for (int c = 0; c < vd->vdev_children; c++)
		vdev_set_min_asize(vd->vdev_child[c]);
}