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
struct usb_endpoint_descriptor {int bEndpointAddress; int bmAttributes; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_endpoint {struct usb_endpoint_descriptor* edesc; } ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {int /*<<< orphan*/  bus; TYPE_1__ flags; } ;
struct musbotg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  musbotg_clear_stall_sub (struct musbotg_softc*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
musbotg_clear_stall(struct usb_device *udev, struct usb_endpoint *ep)
{
	struct musbotg_softc *sc;
	struct usb_endpoint_descriptor *ed;

	DPRINTFN(4, "endpoint=%p\n", ep);

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	/* check mode */
	if (udev->flags.usb_mode != USB_MODE_DEVICE) {
		/* not supported */
		return;
	}
	/* get softc */
	sc = MUSBOTG_BUS2SC(udev->bus);

	/* get endpoint descriptor */
	ed = ep->edesc;

	/* reset endpoint */
	musbotg_clear_stall_sub(sc,
	    UGETW(ed->wMaxPacketSize),
	    (ed->bEndpointAddress & UE_ADDR),
	    (ed->bmAttributes & UE_XFERTYPE),
	    (ed->bEndpointAddress & (UE_DIR_IN | UE_DIR_OUT)));
}