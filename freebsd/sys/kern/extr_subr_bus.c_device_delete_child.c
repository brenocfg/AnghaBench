#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kobj_t ;
typedef  TYPE_1__* device_t ;
struct TYPE_11__ {int /*<<< orphan*/  children; scalar_t__ parent; scalar_t__ devclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CHILD_DELETED (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_data_devices ; 
 int /*<<< orphan*/  bus_data_generation_update () ; 
 int /*<<< orphan*/  devclass_delete_device (scalar_t__,TYPE_1__*) ; 
 int device_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  devlink ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

int
device_delete_child(device_t dev, device_t child)
{
	int error;
	device_t grandchild;

	PDEBUG(("%s from %s", DEVICENAME(child), DEVICENAME(dev)));

	/* detach parent before deleting children, if any */
	if ((error = device_detach(child)) != 0)
		return (error);
	
	/* remove children second */
	while ((grandchild = TAILQ_FIRST(&child->children)) != NULL) {
		error = device_delete_child(child, grandchild);
		if (error)
			return (error);
	}

	if (child->devclass)
		devclass_delete_device(child->devclass, child);
	if (child->parent)
		BUS_CHILD_DELETED(dev, child);
	TAILQ_REMOVE(&dev->children, child, link);
	TAILQ_REMOVE(&bus_data_devices, child, devlink);
	kobj_delete((kobj_t) child, M_BUS);

	bus_data_generation_update();
	return (0);
}