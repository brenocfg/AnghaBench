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
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xs_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xenbusb_verify_device(device_t dev, device_t child)
{
	if (xs_exists(XST_NIL, xenbus_get_node(child), "") == 0) {

		/*
		 * Device tree has been removed from Xenbus.
		 * Tear down the device.
		 */
		xenbusb_delete_child(dev, child);
	}
}