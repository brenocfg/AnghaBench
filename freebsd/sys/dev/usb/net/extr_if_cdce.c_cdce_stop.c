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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct cdce_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t CDCE_BULK_RX ; 
 size_t CDCE_BULK_TX ; 
 size_t CDCE_INTR_RX ; 
 size_t CDCE_INTR_TX ; 
 int /*<<< orphan*/  CDCE_LOCK_ASSERT (struct cdce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cdce_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdce_stop(struct usb_ether *ue)
{
	struct cdce_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	CDCE_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	/*
	 * stop all the transfers, if not already stopped:
	 */
	usbd_transfer_stop(sc->sc_xfer[CDCE_BULK_RX]);
	usbd_transfer_stop(sc->sc_xfer[CDCE_BULK_TX]);
	usbd_transfer_stop(sc->sc_xfer[CDCE_INTR_RX]);
	usbd_transfer_stop(sc->sc_xfer[CDCE_INTR_TX]);
}