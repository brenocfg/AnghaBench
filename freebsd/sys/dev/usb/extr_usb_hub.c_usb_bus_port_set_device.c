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
typedef  size_t uint8_t ;
struct usb_port {size_t device_index; } ;
struct usb_device {int dummy; } ;
struct usb_bus {struct usb_device** devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_bus*,size_t,struct usb_device*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ref_lock ; 

void
usb_bus_port_set_device(struct usb_bus *bus, struct usb_port *up,
    struct usb_device *udev, uint8_t device_index)
{
	if (bus == NULL) {
		/* be NULL safe */
		return;
	}
	/*
	 * There is only one case where we don't
	 * have an USB port, and that is the Root Hub!
         */
	if (up) {
		if (udev) {
			up->device_index = device_index;
		} else {
			device_index = up->device_index;
			up->device_index = 0;
		}
	}
	/*
	 * Make relationships to our new device
	 */
	if (device_index != 0) {
#if USB_HAVE_UGEN
		mtx_lock(&usb_ref_lock);
#endif
		bus->devices[device_index] = udev;
#if USB_HAVE_UGEN
		mtx_unlock(&usb_ref_lock);
#endif
	}
	/*
	 * Debug print
	 */
	DPRINTFN(2, "bus %p devices[%u] = %p\n", bus, device_index, udev);
}