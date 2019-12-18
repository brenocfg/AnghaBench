#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev_children; int /*<<< orphan*/  dev_module; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_link ; 
 int /*<<< orphan*/  devclass_delete_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int device_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  device_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
device_delete_child(device_t dev, device_t child)
{
	int error = 0;
	device_t grandchild;

	/* detach parent before deleting children, if any */
	error = device_detach(child);
	if (error)
		goto done;

	/* remove children second */
	while ((grandchild = TAILQ_FIRST(&child->dev_children))) {
		error = device_delete_child(child, grandchild);
		if (error) {
			device_printf(dev, "Error deleting child!\n");
			goto done;
		}
	}

	devclass_delete_device(child->dev_module, child);

	if (dev != NULL) {
		/* remove child from parent */
		TAILQ_REMOVE(&dev->dev_children, child, dev_link);
	}
	free(child, M_DEVBUF);

done:
	return (error);
}