#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_xfer {TYPE_4__* endpoint; int /*<<< orphan*/  max_frame_size; TYPE_1__* xroot; } ;
struct TYPE_6__ {scalar_t__ usb_mode; } ;
struct usb_device {TYPE_2__ flags; } ;
struct TYPE_8__ {scalar_t__ refcount_bw; int usb_uframe; int usb_smask; int /*<<< orphan*/  usb_cmask; TYPE_3__* edesc; } ;
struct TYPE_7__ {int bmAttributes; } ;
struct TYPE_5__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int) ; 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 
 scalar_t__ USB_MODE_HOST ; 
 int /*<<< orphan*/  usb_hs_bandwidth_adjust (struct usb_device*,int /*<<< orphan*/ ,int,int) ; 

void
usb_hs_bandwidth_free(struct usb_xfer *xfer)
{
	struct usb_device *udev;
	uint8_t slot;
	uint8_t mask;

	udev = xfer->xroot->udev;

	if (udev->flags.usb_mode != USB_MODE_HOST)
		return;		/* not supported */

	xfer->endpoint->refcount_bw--;
	if (xfer->endpoint->refcount_bw != 0)
		return;		/* still allocated */

	switch (xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE) {
	case UE_INTERRUPT:
	case UE_ISOCHRONOUS:

		slot = xfer->endpoint->usb_uframe;
		mask = xfer->endpoint->usb_smask;

		/* free microframe slot(s): */ 	  
		usb_hs_bandwidth_adjust(udev,
		    -xfer->max_frame_size, slot, mask >> slot);

		DPRINTFN(11, "slot=%d, mask=0x%02x\n", 
		    slot, mask >> slot);

		xfer->endpoint->usb_uframe = 0;
		xfer->endpoint->usb_cmask = 0;
		xfer->endpoint->usb_smask = 0;
		break;

	default:
		break;
	}
}