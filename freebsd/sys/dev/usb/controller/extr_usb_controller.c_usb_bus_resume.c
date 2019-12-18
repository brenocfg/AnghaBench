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
struct usb_bus {int hw_power_state; int /*<<< orphan*/ * bdev; TYPE_1__* methods; scalar_t__ no_explore; struct usb_device** devices; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_hw_power ) (struct usb_bus*) ;int /*<<< orphan*/  (* set_hw_power_sleep ) (struct usb_bus*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVMETHOD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int USB_HW_POWER_BULK ; 
 int USB_HW_POWER_CONTROL ; 
 int USB_HW_POWER_INTERRUPT ; 
 int USB_HW_POWER_ISOC ; 
 int USB_HW_POWER_NON_ROOT_HUB ; 
 int /*<<< orphan*/  USB_HW_POWER_RESUME ; 
 int /*<<< orphan*/  USB_IFACE_INDEX_ANY ; 
 size_t USB_ROOT_HUB_ADDR ; 
 int /*<<< orphan*/  USB_TAKE_CONTROLLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct usb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct usb_bus*) ; 
 scalar_t__ usb_probe_and_attach (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_take_controller ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 scalar_t__ usbd_set_config_index (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_bus_resume(struct usb_proc_msg *pm)
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

	do_unlock = usbd_enum_lock(udev);
#if 0
	DEVMETHOD(usb_take_controller, NULL);	/* dummy */
#endif
	USB_TAKE_CONTROLLER(device_get_parent(bus->bdev));

	USB_BUS_LOCK(bus);
 	bus->hw_power_state =
	  USB_HW_POWER_CONTROL |
	  USB_HW_POWER_BULK |
	  USB_HW_POWER_INTERRUPT |
	  USB_HW_POWER_ISOC |
	  USB_HW_POWER_NON_ROOT_HUB;
	bus->no_explore = 0;
	USB_BUS_UNLOCK(bus);

	if (bus->methods->set_hw_power_sleep != NULL)
		(bus->methods->set_hw_power_sleep) (bus, USB_HW_POWER_RESUME);

	if (bus->methods->set_hw_power != NULL)
		(bus->methods->set_hw_power) (bus);

	/* restore USB configuration to index 0 */
	err = usbd_set_config_index(udev, 0);
	if (err)
		device_printf(bus->bdev, "Could not configure root HUB\n");

	/* probe and attach */
	err = usb_probe_and_attach(udev, USB_IFACE_INDEX_ANY);
	if (err) {
		device_printf(bus->bdev, "Could not probe and "
		    "attach root HUB\n");
	}

	if (do_unlock)
		usbd_enum_unlock(udev);

	USB_BUS_LOCK(bus);
}