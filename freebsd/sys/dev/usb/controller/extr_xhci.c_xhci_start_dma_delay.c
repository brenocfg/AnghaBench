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
struct TYPE_4__ {int /*<<< orphan*/  intr_q; } ;
struct xhci_softc {int /*<<< orphan*/ * sc_config_msg; TYPE_2__ sc_bus; } ;
struct usb_xfer {TYPE_1__* xroot; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_CONTROL_XFER_PROC (TYPE_2__*) ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (int /*<<< orphan*/ *,struct usb_xfer*) ; 

__attribute__((used)) static void
xhci_start_dma_delay(struct usb_xfer *xfer)
{
	struct xhci_softc *sc = XHCI_BUS2SC(xfer->xroot->bus);

	/* put transfer on interrupt queue (again) */
	usbd_transfer_enqueue(&sc->sc_bus.intr_q, xfer);

	(void)usb_proc_msignal(USB_BUS_CONTROL_XFER_PROC(&sc->sc_bus),
	    &sc->sc_config_msg[0], &sc->sc_config_msg[1]);
}