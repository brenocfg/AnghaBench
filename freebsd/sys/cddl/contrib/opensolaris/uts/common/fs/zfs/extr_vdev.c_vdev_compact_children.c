#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_children; struct TYPE_5__** vdev_child; int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 TYPE_1__** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,int) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
vdev_compact_children(vdev_t *pvd)
{
	vdev_t **newchild, *cvd;
	int oldc = pvd->vdev_children;
	int newc;

	ASSERT(spa_config_held(pvd->vdev_spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	if (oldc == 0)
		return;

	for (int c = newc = 0; c < oldc; c++)
		if (pvd->vdev_child[c])
			newc++;

	if (newc > 0) {
		newchild = kmem_alloc(newc * sizeof (vdev_t *), KM_SLEEP);

		for (int c = newc = 0; c < oldc; c++) {
			if ((cvd = pvd->vdev_child[c]) != NULL) {
				newchild[newc] = cvd;
				cvd->vdev_id = newc++;
			}
		}
	} else {
		newchild = NULL;
	}

	kmem_free(pvd->vdev_child, oldc * sizeof (vdev_t *));
	pvd->vdev_child = newchild;
	pvd->vdev_children = newc;
}