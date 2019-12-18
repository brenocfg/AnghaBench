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
struct kue_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 size_t KUE_BULK_DT_WR ; 
 int /*<<< orphan*/  KUE_CMD_SET_MAC ; 
 int /*<<< orphan*/  KUE_CMD_SET_SOFS ; 
 int /*<<< orphan*/  KUE_CMD_SET_URB_SIZE ; 
 int /*<<< orphan*/  KUE_CTL_WRITE ; 
 int /*<<< orphan*/  KUE_LOCK_ASSERT (struct kue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  kue_ctl (struct kue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kue_setpromisc (struct usb_ether*) ; 
 int /*<<< orphan*/  kue_setword (struct kue_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kue_start (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct kue_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kue_init(struct usb_ether *ue)
{
	struct kue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	KUE_LOCK_ASSERT(sc, MA_OWNED);

	/* set MAC address */
	kue_ctl(sc, KUE_CTL_WRITE, KUE_CMD_SET_MAC,
	    0, IF_LLADDR(ifp), ETHER_ADDR_LEN);

	/* I'm not sure how to tune these. */
#if 0
	/*
	 * Leave this one alone for now; setting it
	 * wrong causes lockups on some machines/controllers.
	 */
	kue_setword(sc, KUE_CMD_SET_SOFS, 1);
#endif
	kue_setword(sc, KUE_CMD_SET_URB_SIZE, 64);

	/* load the multicast filter */
	kue_setpromisc(ue);

	usbd_xfer_set_stall(sc->sc_xfer[KUE_BULK_DT_WR]);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	kue_start(ue);
}