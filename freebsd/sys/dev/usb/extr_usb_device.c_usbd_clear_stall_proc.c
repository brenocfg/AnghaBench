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
struct usb_udev_msg {struct usb_device* udev; } ;
struct usb_proc_msg {int dummy; } ;
struct usb_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  device_mtx; int /*<<< orphan*/ * ctrl_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbd_clear_stall_proc(struct usb_proc_msg *_pm)
{
	struct usb_udev_msg *pm = (void *)_pm;
	struct usb_device *udev = pm->udev;

	/* Change lock */
	USB_BUS_UNLOCK(udev->bus);
	USB_MTX_LOCK(&udev->device_mtx);

	/* Start clear stall callback */
	usbd_transfer_start(udev->ctrl_xfer[1]);

	/* Change lock */
	USB_MTX_UNLOCK(&udev->device_mtx);
	USB_BUS_LOCK(udev->bus);
}