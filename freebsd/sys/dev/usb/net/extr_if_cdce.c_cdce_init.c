#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_ether {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; } ;
struct cdce_softc {int /*<<< orphan*/ * sc_xfer; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 size_t CDCE_BULK_TX ; 
 size_t CDCE_INTR_RX ; 
 size_t CDCE_INTR_TX ; 
 int /*<<< orphan*/  CDCE_LOCK_ASSERT (struct cdce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ USB_MODE_HOST ; 
 int /*<<< orphan*/  cdce_start (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cdce_softc* uether_getsc (struct usb_ether*) ; 
 scalar_t__ usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdce_init(struct usb_ether *ue)
{
	struct cdce_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	CDCE_LOCK_ASSERT(sc, MA_OWNED);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	/* start interrupt transfer */
	usbd_transfer_start(sc->sc_xfer[CDCE_INTR_RX]);
	usbd_transfer_start(sc->sc_xfer[CDCE_INTR_TX]);

	/*
	 * Stall data write direction, which depends on USB mode.
	 *
	 * Some USB host stacks (e.g. Mac OS X) don't clears stall
	 * bit as it should, so set it in our host mode only.
	 */
	if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST)
		usbd_xfer_set_stall(sc->sc_xfer[CDCE_BULK_TX]);

	/* start data transfers */
	cdce_start(ue);
}