#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct uss820dci_softc {int /*<<< orphan*/  sc_bus; } ;
struct TYPE_3__ {scalar_t__ usb_mode; } ;
struct usb_xfer {TYPE_1__ flags_int; int /*<<< orphan*/  endpoint; TYPE_2__* xroot; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uss820dci_intr_set (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uss820dci_device_done(struct usb_xfer *xfer, usb_error_t error)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(xfer->xroot->bus);

	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

	DPRINTFN(2, "xfer=%p, endpoint=%p, error=%d\n",
	    xfer, xfer->endpoint, error);

	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {
		uss820dci_intr_set(xfer, 0);
	}
	/* dequeue transfer and start next transfer */
	usbd_transfer_done(xfer, error);

	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
}