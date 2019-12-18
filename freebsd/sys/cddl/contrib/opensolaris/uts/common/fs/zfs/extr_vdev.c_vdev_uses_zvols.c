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
struct TYPE_3__ {int vdev_children; struct TYPE_3__** vdev_child; scalar_t__ vdev_path; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ZVOL_DIR ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
vdev_uses_zvols(vdev_t *vd)
{
	if (vd->vdev_path && strncmp(vd->vdev_path, ZVOL_DIR,
	    strlen(ZVOL_DIR)) == 0)
		return (B_TRUE);
	for (int c = 0; c < vd->vdev_children; c++)
		if (vdev_uses_zvols(vd->vdev_child[c]))
			return (B_TRUE);
	return (B_FALSE);
}