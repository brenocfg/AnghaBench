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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_xfer {TYPE_1__* xroot; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_get_ep_by_addr (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_set_endpoint_stall (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
usb_handle_set_stall(struct usb_xfer *xfer, uint8_t ep, uint8_t do_stall)
{
	struct usb_device *udev = xfer->xroot->udev;
	usb_error_t err;

	USB_XFER_UNLOCK(xfer);
	err = usbd_set_endpoint_stall(udev,
	    usbd_get_ep_by_addr(udev, ep), do_stall);
	USB_XFER_LOCK(xfer);
	return (err);
}