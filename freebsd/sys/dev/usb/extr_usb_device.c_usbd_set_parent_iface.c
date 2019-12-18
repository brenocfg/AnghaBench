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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_interface {int /*<<< orphan*/  parent_iface_index; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_interface* usbd_get_iface (struct usb_device*,int /*<<< orphan*/ ) ; 

void
usbd_set_parent_iface(struct usb_device *udev, uint8_t iface_index,
    uint8_t parent_index)
{
	struct usb_interface *iface;

	if (udev == NULL) {
		/* nothing to do */
		return;
	}
	iface = usbd_get_iface(udev, iface_index);
	if (iface != NULL)
		iface->parent_iface_index = parent_index;
}