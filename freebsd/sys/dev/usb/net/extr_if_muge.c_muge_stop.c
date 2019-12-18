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
struct muge_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_flags; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t MUGE_BULK_DT_RD ; 
 size_t MUGE_BULK_DT_WR ; 
 int /*<<< orphan*/  MUGE_FLAG_LINK ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
muge_stop(struct usb_ether *ue)
{
	struct muge_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->sc_flags &= ~MUGE_FLAG_LINK;

	/*
	 * Stop all the transfers, if not already stopped.
	 */
	usbd_transfer_stop(sc->sc_xfer[MUGE_BULK_DT_WR]);
	usbd_transfer_stop(sc->sc_xfer[MUGE_BULK_DT_RD]);
}