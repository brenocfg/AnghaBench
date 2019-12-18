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
struct TYPE_2__ {int /*<<< orphan*/ * node; } ;
struct xenbus_device_ivars {TYPE_1__ xd_local_watch; TYPE_1__ xd_otherend_watch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_free_child_ivars (struct xenbus_device_ivars*) ; 
 int /*<<< orphan*/  xs_unregister_watch (TYPE_1__*) ; 

__attribute__((used)) static void
xenbusb_delete_child(device_t dev, device_t child)
{
	struct xenbus_device_ivars *ivars;

	ivars = device_get_ivars(child);

	/*
	 * We no longer care about the otherend of the
	 * connection.  Cancel the watches now so that we
	 * don't try to handle an event for a partially
	 * detached child.
	 */
	if (ivars->xd_otherend_watch.node != NULL)
		xs_unregister_watch(&ivars->xd_otherend_watch);
	if (ivars->xd_local_watch.node != NULL)
		xs_unregister_watch(&ivars->xd_local_watch);
	
	device_delete_child(dev, child);
	xenbusb_free_child_ivars(ivars);
}