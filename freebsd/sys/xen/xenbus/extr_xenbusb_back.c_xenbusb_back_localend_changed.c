#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XST_NIL ; 
 scalar_t__ XenbusStateClosed ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ xenbus_dev_is_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_localend_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xs_rm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xenbusb_back_localend_changed(device_t bus, device_t child, const char *path)
{

	xenbusb_localend_changed(bus, child, path);

	if (strcmp(path, "/state") != 0
	 && strcmp(path, "/online") != 0)
		return;

	if (xenbus_get_state(child) != XenbusStateClosed
	 || xenbus_dev_is_online(child) != 0)
		return;

	/*
	 * Cleanup the hotplug entry in the XenStore if
	 * present.  The control domain expects any userland
	 * component associated with this device to destroy
	 * this node in order to signify it is safe to 
	 * teardown the device.  However, not all backends
	 * rely on userland components, and those that
	 * do should either use a communication channel
	 * other than the XenStore, or ensure the hotplug
	 * data is already cleaned up.
	 *
	 * This removal ensures that no matter what path
	 * is taken to mark a back-end closed, the control
	 * domain will understand that it is closed.
	 */
	xs_rm(XST_NIL, xenbus_get_node(child), "hotplug-status");
}