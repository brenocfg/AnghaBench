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
struct usb_xfer {scalar_t__ timeout; TYPE_1__* xroot; } ;
struct saf1761_otg_softc {int /*<<< orphan*/  sc_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  intr_q; } ;
struct TYPE_3__ {TYPE_2__* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 struct saf1761_otg_softc* SAF1761_OTG_BUS2SC (TYPE_2__*) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saf1761_otg_intr_set (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  saf1761_otg_timeout ; 
 scalar_t__ saf1761_otg_xfer_do_complete (struct saf1761_otg_softc*,struct usb_xfer*) ; 
 int /*<<< orphan*/  saf1761_otg_xfer_do_fifo (struct saf1761_otg_softc*,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
saf1761_otg_start_standard_chain(struct usb_xfer *xfer)
{
	struct saf1761_otg_softc *sc = SAF1761_OTG_BUS2SC(xfer->xroot->bus);

	DPRINTFN(9, "\n");

	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	/* poll one time */
	saf1761_otg_xfer_do_fifo(sc, xfer);

	if (saf1761_otg_xfer_do_complete(sc, xfer) == 0) {
		/*
		 * Only enable the endpoint interrupt when we are
		 * actually waiting for data, hence we are dealing
		 * with level triggered interrupts !
		 */
		saf1761_otg_intr_set(xfer, 1);

		/* put transfer on interrupt queue */
		usbd_transfer_enqueue(&xfer->xroot->bus->intr_q, xfer);

		/* start timeout, if any */
		if (xfer->timeout != 0) {
			usbd_transfer_timeout_ms(xfer,
			    &saf1761_otg_timeout, xfer->timeout);
		}
	}
	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
}