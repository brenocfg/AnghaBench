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
struct TYPE_4__ {int vdev_children; struct TYPE_4__** vdev_child; struct TYPE_4__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */

__attribute__((used)) static void
vdev_top_update(vdev_t *tvd, vdev_t *vd)
{
	if (vd == NULL)
		return;

	vd->vdev_top = tvd;

	for (int c = 0; c < vd->vdev_children; c++)
		vdev_top_update(tvd, vd->vdev_child[c]);
}