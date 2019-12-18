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
struct usb_port {size_t device_index; } ;
struct usb_device {int dummy; } ;
struct usb_bus {struct usb_device** devices; } ;

/* Variables and functions */

struct usb_device *
usb_bus_port_get_device(struct usb_bus *bus, struct usb_port *up)
{
	if ((bus == NULL) || (up == NULL)) {
		/* be NULL safe */
		return (NULL);
	}
	if (up->device_index == 0) {
		/* nothing to do */
		return (NULL);
	}
	return (bus->devices[up->device_index]);
}