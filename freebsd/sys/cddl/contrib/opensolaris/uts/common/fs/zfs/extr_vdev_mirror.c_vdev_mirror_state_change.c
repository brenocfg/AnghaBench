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
struct TYPE_5__ {int vdev_children; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  VDEV_AUX_CHILDREN_OFFLINE ; 
 int /*<<< orphan*/  VDEV_AUX_NONE ; 
 int /*<<< orphan*/  VDEV_AUX_NO_REPLICAS ; 
 int /*<<< orphan*/  VDEV_STATE_CANT_OPEN ; 
 int /*<<< orphan*/  VDEV_STATE_DEGRADED ; 
 int /*<<< orphan*/  VDEV_STATE_HEALTHY ; 
 int /*<<< orphan*/  VDEV_STATE_OFFLINE ; 
 scalar_t__ vdev_children_are_offline (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_set_state (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_mirror_state_change(vdev_t *vd, int faulted, int degraded)
{
	if (faulted == vd->vdev_children) {
		if (vdev_children_are_offline(vd)) {
			vdev_set_state(vd, B_FALSE, VDEV_STATE_OFFLINE,
			    VDEV_AUX_CHILDREN_OFFLINE);
		} else {
			vdev_set_state(vd, B_FALSE, VDEV_STATE_CANT_OPEN,
			    VDEV_AUX_NO_REPLICAS);
		}
	} else if (degraded + faulted != 0) {
		vdev_set_state(vd, B_FALSE, VDEV_STATE_DEGRADED, VDEV_AUX_NONE);
	} else {
		vdev_set_state(vd, B_FALSE, VDEV_STATE_HEALTHY, VDEV_AUX_NONE);
	}
}