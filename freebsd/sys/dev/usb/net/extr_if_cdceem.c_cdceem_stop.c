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
struct cdceem_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t CDCEEM_BULK_RX ; 
 size_t CDCEEM_BULK_TX ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cdceem_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdceem_stop(struct usb_ether *ue)
{
	struct cdceem_softc *sc;
	struct ifnet *ifp;

	sc = uether_getsc(ue);
	ifp = uether_getifp(ue);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	usbd_transfer_stop(sc->sc_xfer[CDCEEM_BULK_RX]);
	usbd_transfer_stop(sc->sc_xfer[CDCEEM_BULK_TX]);
}