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
struct TYPE_4__ {int vdev_children; struct TYPE_4__** vdev_child; scalar_t__ vdev_probe_wanted; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_1__*) ; 

__attribute__((used)) static void
spa_async_probe(spa_t *spa, vdev_t *vd)
{
	if (vd->vdev_probe_wanted) {
		vd->vdev_probe_wanted = B_FALSE;
		vdev_reopen(vd);	/* vdev_open() does the actual probe */
	}

	for (int c = 0; c < vd->vdev_children; c++)
		spa_async_probe(spa, vd->vdev_child[c]);
}