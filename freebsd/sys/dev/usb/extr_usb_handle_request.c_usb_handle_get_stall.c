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
struct usb_endpoint {int /*<<< orphan*/  is_stalled; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 struct usb_endpoint* usbd_get_ep_by_addr (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
usb_handle_get_stall(struct usb_device *udev, uint8_t ea_val)
{
	struct usb_endpoint *ep;
	uint8_t halted;

	ep = usbd_get_ep_by_addr(udev, ea_val);
	if (ep == NULL) {
		/* nothing to do */
		return (0);
	}
	USB_BUS_LOCK(udev->bus);
	halted = ep->is_stalled;
	USB_BUS_UNLOCK(udev->bus);

	return (halted);
}