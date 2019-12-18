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
struct usb_xfer {TYPE_4__* endpoint; TYPE_1__* xroot; } ;
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int address; TYPE_2__ ddesc; } ;
struct TYPE_8__ {TYPE_3__* edesc; } ;
struct TYPE_7__ {int bEndpointAddress; int bmAttributes; } ;
struct TYPE_5__ {struct usb_device* udev; } ;

/* Variables and functions */
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,struct usb_xfer*,...) ; 

void
usb_dump_xfer(struct usb_xfer *xfer)
{
	struct usb_device *udev;
	printf("usb_dump_xfer: xfer=%p\n", xfer);
	if (xfer == NULL) {
		return;
	}
	if (xfer->endpoint == NULL) {
		printf("xfer %p: endpoint=NULL\n",
		    xfer);
		return;
	}
	udev = xfer->xroot->udev;
	printf("xfer %p: udev=%p vid=0x%04x pid=0x%04x addr=%d "
	    "endpoint=%p ep=0x%02x attr=0x%02x\n",
	    xfer, udev,
	    UGETW(udev->ddesc.idVendor),
	    UGETW(udev->ddesc.idProduct),
	    udev->address, xfer->endpoint,
	    xfer->endpoint->edesc->bEndpointAddress,
	    xfer->endpoint->edesc->bmAttributes);
}