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
struct ipheth_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 size_t IPHETH_BULK_TX ; 
 int /*<<< orphan*/  IPHETH_LOCK_ASSERT (struct ipheth_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  ipheth_start (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct ipheth_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipheth_init(struct usb_ether *ue)
{
	struct ipheth_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	IPHETH_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	/* stall data write direction, which depends on USB mode */
	usbd_xfer_set_stall(sc->sc_xfer[IPHETH_BULK_TX]);

	/* start data transfers */
	ipheth_start(ue);
}