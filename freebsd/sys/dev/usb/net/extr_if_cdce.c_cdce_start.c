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
struct usb_ether {int dummy; } ;
struct cdce_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t CDCE_BULK_RX ; 
 size_t CDCE_BULK_TX ; 
 struct cdce_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdce_start(struct usb_ether *ue)
{
	struct cdce_softc *sc = uether_getsc(ue);

	/*
	 * Start the USB transfers, if not already started:
	 */
	usbd_transfer_start(sc->sc_xfer[CDCE_BULK_TX]);
	usbd_transfer_start(sc->sc_xfer[CDCE_BULK_RX]);
}