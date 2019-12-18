#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {struct usb_device* parent_hub; TYPE_1__* bus; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX_UDEV_NEST ; 
 int find_udev_in_children (int,struct usb_device*) ; 
 int nitems (struct usb_device**) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

phandle_t
usb_fdt_get_node(device_t dev, struct usb_device *udev)
{
	struct usb_device *ud;
	struct usb_device *udev_stack[MAX_UDEV_NEST];
	phandle_t controller_node, node;
	int idx;

	/*
	 * Start searching at the controller node.  The usb_device links to the
	 * bus, and its parent is the controller.  If we can't get the
	 * controller node, the requesting device cannot be in the fdt data.
	 */
	if ((controller_node = ofw_bus_get_node(udev->bus->parent)) == -1)
		return (-1);

	/*
	 * Walk up the usb hub ancestor hierarchy, building a stack of devices
	 * that begins with the requesting device and includes all the hubs
	 * between it and the controller, NOT including the root hub (the FDT
	 * bindings treat the controller and root hub as the same thing).
	 */
	for (ud = udev, idx = 0; ud->parent_hub != NULL; ud = ud->parent_hub) {
		KASSERT(idx < nitems(udev_stack), ("Too many hubs"));
		udev_stack[idx++] = ud;
	}

	/*
	 * Now walk down the stack of udevs from the controller to the
	 * requesting device, and also down the hierarchy of nested children of
	 * the controller node in the fdt data.  At each nesting level of fdt
	 * data look for a child node whose properties match the vID,pID,portIdx
	 * tuple for the udev at the corresponding layer of the udev stack.  As
	 * long as we keep matching up child nodes with udevs, loop and search
	 * within the children of the just-found child for the next-deepest hub.
	 * If at any level we fail to find a matching node, stop searching and
	 * return.  When we hit the end of the stack (the requesting device) we
	 * return whatever the result was for the search at that nesting level.
	 */
	for (node = controller_node;;) {
		node = find_udev_in_children(node, udev_stack[--idx]);
		if (idx == 0 || node == -1)
			break;
	}
	return (node);
}