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
struct muge_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t MUGE_BULK_DT_WR ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ lan78xx_setmacaddress (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 int /*<<< orphan*/  muge_ifmedia_upd (struct ifnet*) ; 
 int /*<<< orphan*/  muge_reset (struct muge_softc*) ; 
 int /*<<< orphan*/  muge_sethwcsum (struct muge_softc*) ; 
 int /*<<< orphan*/  muge_setmulti (struct usb_ether*) ; 
 int /*<<< orphan*/  muge_start (struct usb_ether*) ; 
 int /*<<< orphan*/  muge_stop (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
muge_init(struct usb_ether *ue)
{
	struct muge_softc *sc = uether_getsc(ue);
	muge_dbg_printf(sc, "Calling muge_init.\n");
	struct ifnet *ifp = uether_getifp(ue);
	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	if (lan78xx_setmacaddress(sc, IF_LLADDR(ifp)))
		muge_dbg_printf(sc, "setting MAC address failed\n");

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O. */
	muge_stop(ue);

	/* Reset the ethernet interface. */
	muge_reset(sc);

	/* Load the multicast filter. */
	muge_setmulti(ue);

	/* TCP/UDP checksum offload engines. */
	muge_sethwcsum(sc);

	usbd_xfer_set_stall(sc->sc_xfer[MUGE_BULK_DT_WR]);

	/* Indicate we are up and running. */
	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	/* Switch to selected media. */
	muge_ifmedia_upd(ifp);
	muge_start(ue);
}