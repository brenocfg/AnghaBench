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
struct TYPE_3__ {int vdev_children; int /*<<< orphan*/ * vdev_child; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_mirror_close(vdev_t *vd)
{
	for (int c = 0; c < vd->vdev_children; c++)
		vdev_close(vd->vdev_child[c]);
}