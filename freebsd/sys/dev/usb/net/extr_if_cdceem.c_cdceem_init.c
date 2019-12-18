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
struct cdceem_softc {int /*<<< orphan*/ * sc_xfer; TYPE_1__ sc_ue; scalar_t__ sc_flags; } ;

/* Variables and functions */
 size_t CDCEEM_BULK_TX ; 
 scalar_t__ CDCEEM_SC_FLAGS_ECHO_PENDING ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 scalar_t__ USB_MODE_HOST ; 
 scalar_t__ cdceem_send_echoes ; 
 int /*<<< orphan*/  cdceem_start (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cdceem_softc* uether_getsc (struct usb_ether*) ; 
 scalar_t__ usbd_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdceem_init(struct usb_ether *ue)
{
	struct cdceem_softc *sc;
	struct ifnet *ifp;

	sc = uether_getsc(ue);
	ifp = uether_getifp(ue);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	if (cdceem_send_echoes)
		sc->sc_flags = CDCEEM_SC_FLAGS_ECHO_PENDING;
	else
		sc->sc_flags = 0;

	/*
	 * Stall data write direction, which depends on USB mode.
	 *
	 * Some USB host stacks (e.g. Mac OS X) don't clears stall
	 * bit as it should, so set it in our host mode only.
	 */
	if (usbd_get_mode(sc->sc_ue.ue_udev) == USB_MODE_HOST)
		usbd_xfer_set_stall(sc->sc_xfer[CDCEEM_BULK_TX]);

	cdceem_start(ue);
}