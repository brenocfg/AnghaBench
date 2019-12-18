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
struct usb_bus {int /*<<< orphan*/  bus_roothold; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 struct usb_bus* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  root_mount_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_attach_sub (int /*<<< orphan*/ ,struct usb_bus*) ; 
 scalar_t__ usb_no_boot_wait ; 

__attribute__((used)) static int
usb_attach(device_t dev)
{
	struct usb_bus *bus = device_get_ivars(dev);

	DPRINTF("\n");

	if (bus == NULL) {
		device_printf(dev, "USB device has no ivars\n");
		return (ENXIO);
	}

#if USB_HAVE_ROOT_MOUNT_HOLD
	if (usb_no_boot_wait == 0) {
		/* delay vfs_mountroot until the bus is explored */
		bus->bus_roothold = root_mount_hold(device_get_nameunit(dev));
	}
#endif
	usb_attach_sub(dev, bus);

	return (0);			/* return success */
}