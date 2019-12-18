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
struct mos_softc {scalar_t__ mos_link; int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t MOS_ENDPT_INTR ; 
 size_t MOS_ENDPT_RX ; 
 size_t MOS_ENDPT_TX ; 
 int /*<<< orphan*/  MOS_LOCK_ASSERT (struct mos_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_reset (struct mos_softc*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct mos_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mos_stop(struct usb_ether *ue)
{
	struct mos_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	mos_reset(sc);

	MOS_LOCK_ASSERT(sc, MA_OWNED);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	/* stop all the transfers, if not already stopped */
	usbd_transfer_stop(sc->sc_xfer[MOS_ENDPT_TX]);
	usbd_transfer_stop(sc->sc_xfer[MOS_ENDPT_RX]);
	usbd_transfer_stop(sc->sc_xfer[MOS_ENDPT_INTR]);

	sc->mos_link = 0;
}