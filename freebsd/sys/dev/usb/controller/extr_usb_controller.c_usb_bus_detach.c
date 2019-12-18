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
struct usb_proc_msg {int dummy; } ;
struct usb_device {int dummy; } ;
struct usb_bus_msg {struct usb_bus* bus; } ;
struct usb_bus {int /*<<< orphan*/ * bdev; struct usb_device** devices; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 size_t USB_ROOT_HUB_ADDR ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_device (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_bus_detach(struct usb_proc_msg *pm)
{
	struct usb_bus *bus;
	struct usb_device *udev;
	device_t dev;

	bus = ((struct usb_bus_msg *)pm)->bus;
	udev = bus->devices[USB_ROOT_HUB_ADDR];
	dev = bus->bdev;
	/* clear the softc */
	device_set_softc(dev, NULL);
	USB_BUS_UNLOCK(bus);

	/* detach children first */
	mtx_lock(&Giant);
	bus_generic_detach(dev);
	mtx_unlock(&Giant);

	/*
	 * Free USB device and all subdevices, if any.
	 */
	usb_free_device(udev, 0);

	USB_BUS_LOCK(bus);
	/* clear bdev variable last */
	bus->bdev = NULL;
}