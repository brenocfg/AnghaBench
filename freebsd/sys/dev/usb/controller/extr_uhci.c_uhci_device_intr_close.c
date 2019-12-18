#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * sc_intr_stat; } ;
typedef  TYPE_2__ uhci_softc_t ;
struct usb_xfer {size_t qh_pos; TYPE_1__* xroot; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 TYPE_2__* UHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  uhci_device_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_device_intr_close(struct usb_xfer *xfer)
{
	uhci_softc_t *sc = UHCI_BUS2SC(xfer->xroot->bus);

	sc->sc_intr_stat[xfer->qh_pos]--;

	uhci_device_done(xfer, USB_ERR_CANCELLED);
}