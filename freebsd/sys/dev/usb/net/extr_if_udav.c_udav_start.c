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
struct usb_ether {struct udav_softc* ue_sc; } ;
struct udav_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t UDAV_BULK_DT_RD ; 
 size_t UDAV_BULK_DT_WR ; 
 size_t UDAV_INTR_DT_RD ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
udav_start(struct usb_ether *ue)
{
	struct udav_softc *sc = ue->ue_sc;

	/*
	 * start the USB transfers, if not already started:
	 */
	usbd_transfer_start(sc->sc_xfer[UDAV_INTR_DT_RD]);
	usbd_transfer_start(sc->sc_xfer[UDAV_BULK_DT_RD]);
	usbd_transfer_start(sc->sc_xfer[UDAV_BULK_DT_WR]);
}