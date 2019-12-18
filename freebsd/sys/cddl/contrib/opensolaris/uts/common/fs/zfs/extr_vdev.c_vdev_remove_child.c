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
struct TYPE_5__ {size_t vdev_id; size_t vdev_children; scalar_t__ vdev_guid_sum; struct TYPE_5__* vdev_parent; struct TYPE_5__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,int) ; 

void
vdev_remove_child(vdev_t *pvd, vdev_t *cvd)
{
	int c;
	uint_t id = cvd->vdev_id;

	ASSERT(cvd->vdev_parent == pvd);

	if (pvd == NULL)
		return;

	ASSERT(id < pvd->vdev_children);
	ASSERT(pvd->vdev_child[id] == cvd);

	pvd->vdev_child[id] = NULL;
	cvd->vdev_parent = NULL;

	for (c = 0; c < pvd->vdev_children; c++)
		if (pvd->vdev_child[c])
			break;

	if (c == pvd->vdev_children) {
		kmem_free(pvd->vdev_child, c * sizeof (vdev_t *));
		pvd->vdev_child = NULL;
		pvd->vdev_children = 0;
	}

	/*
	 * Walk up all ancestors to update guid sum.
	 */
	for (; pvd != NULL; pvd = pvd->vdev_parent)
		pvd->vdev_guid_sum -= cvd->vdev_guid_sum;
}