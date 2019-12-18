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
struct TYPE_4__ {scalar_t__ vdev_guid; int vdev_children; struct TYPE_4__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

vdev_t *
vdev_lookup_by_guid(vdev_t *vd, uint64_t guid)
{
	vdev_t *mvd;

	if (vd->vdev_guid == guid)
		return (vd);

	for (int c = 0; c < vd->vdev_children; c++)
		if ((mvd = vdev_lookup_by_guid(vd->vdev_child[c], guid)) !=
		    NULL)
			return (mvd);

	return (NULL);
}