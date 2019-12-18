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
typedef  int uint8_t ;
struct usb_endpoint {TYPE_1__* edesc; } ;
struct usb_device {int /*<<< orphan*/  speed; } ;
struct TYPE_2__ {int bmAttributes; } ;

/* Variables and functions */
 int UE_BULK ; 
 int UE_XFERTYPE ; 
#define  USB_EP_MODE_DEFAULT 129 
#define  USB_EP_MODE_STREAMS 128 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  xhcistreams ; 

__attribute__((used)) static usb_error_t
xhci_set_endpoint_mode(struct usb_device *udev, struct usb_endpoint *ep,
    uint8_t ep_mode)
{
	switch (ep_mode) {
	case USB_EP_MODE_DEFAULT:
		return (0);
	case USB_EP_MODE_STREAMS:
		if (xhcistreams == 0 || 
		    (ep->edesc->bmAttributes & UE_XFERTYPE) != UE_BULK ||
		    udev->speed != USB_SPEED_SUPER)
			return (USB_ERR_INVAL);
		return (0);
	default:
		return (USB_ERR_INVAL);
	}
}