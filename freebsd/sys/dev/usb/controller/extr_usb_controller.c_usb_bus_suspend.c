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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_proc_msg {int dummy; } ;
struct usb_device {int dummy; } ;
struct usb_bus_msg {struct usb_bus* bus; } ;
struct usb_bus {int no_explore; TYPE_1__* methods; scalar_t__ hw_power_state; int /*<<< orphan*/ * bdev; struct usb_device** devices; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_hw_power_sleep ) (struct usb_bus*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_hw_power ) (struct usb_bus*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_HW_POWER_SUSPEND ; 
 size_t USB_ROOT_HUB_ADDR ; 
 int /*<<< orphan*/  USB_UNCONFIG_INDEX ; 
 int /*<<< orphan*/  bus_generic_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct usb_bus*) ; 
 int /*<<< orphan*/  stub2 (struct usb_bus*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 scalar_t__ usbd_set_config_index (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_bus_suspend(struct usb_proc_msg *pm)
{
	struct usb_bus *bus;
	struct usb_device *udev;
	usb_error_t err;
	uint8_t do_unlock;

	DPRINTF("\n");

	bus = ((struct usb_bus_msg *)pm)->bus;
	udev = bus->devices[USB_ROOT_HUB_ADDR];

	if (udev == NULL || bus->bdev == NULL)
		return;

	USB_BUS_UNLOCK(bus);

	/*
	 * We use the shutdown event here because the suspend and
	 * resume events are reserved for the USB port suspend and
	 * resume. The USB system suspend is implemented like full
	 * shutdown and all connected USB devices will be disconnected
	 * subsequently. At resume all USB devices will be
	 * re-connected again.
	 */

	bus_generic_shutdown(bus->bdev);

	do_unlock = usbd_enum_lock(udev);

	err = usbd_set_config_index(udev, USB_UNCONFIG_INDEX);
	if (err)
		device_printf(bus->bdev, "Could not unconfigure root HUB\n");

	USB_BUS_LOCK(bus);
	bus->hw_power_state = 0;
	bus->no_explore = 1;
	USB_BUS_UNLOCK(bus);

	if (bus->methods->set_hw_power != NULL)
		(bus->methods->set_hw_power) (bus);

	if (bus->methods->set_hw_power_sleep != NULL)
		(bus->methods->set_hw_power_sleep) (bus, USB_HW_POWER_SUSPEND);

	if (do_unlock)
		usbd_enum_unlock(udev);

	USB_BUS_LOCK(bus);
}