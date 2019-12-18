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
struct urndis_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t URNDIS_BULK_TX ; 
 int /*<<< orphan*/  URNDIS_LOCK_ASSERT (struct urndis_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct urndis_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  urndis_start (struct usb_ether*) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
urndis_init(struct usb_ether *ue)
{
	struct urndis_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	URNDIS_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	/* stall data write direction, which depends on USB mode */
	usbd_xfer_set_stall(sc->sc_xfer[URNDIS_BULK_TX]);

	/* start data transfers */
	urndis_start(ue);
}