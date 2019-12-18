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
typedef  int uint8_t ;
struct usb_interface {int dummy; } ;
struct usb_device {int ifaces_max; struct usb_interface* ifaces; } ;

/* Variables and functions */

struct usb_interface *
usbd_get_iface(struct usb_device *udev, uint8_t iface_index)
{
	struct usb_interface *iface = udev->ifaces + iface_index;

	if (iface_index >= udev->ifaces_max)
		return (NULL);
	return (iface);
}