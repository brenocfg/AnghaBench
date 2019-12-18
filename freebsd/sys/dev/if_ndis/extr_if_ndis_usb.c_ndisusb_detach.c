#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ndisusb_ep {int /*<<< orphan*/  ne_xfer; } ;
struct TYPE_4__ {int /*<<< orphan*/  ne_xfer; } ;
struct TYPE_3__ {int /*<<< orphan*/  ne_xfer; } ;
struct ndis_softc {int ndisusb_status; int /*<<< orphan*/  ndisusb_mtx; struct ndisusb_ep* ndisusb_ep; TYPE_2__ ndisusb_dwrite_ep; TYPE_1__ ndisusb_dread_ep; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NDISUSB_ENDPT_MAX ; 
 int NDISUSB_STATUS_DETACH ; 
 int NDISUSB_STATUS_SETUP_EP ; 
 int /*<<< orphan*/  NDIS_PNP_EVENT_SURPRISE_REMOVED ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndis_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_pnpevent_nic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ndisusb_detach(device_t self)
{
	int i;
	struct ndis_softc       *sc = device_get_softc(self);
	struct ndisusb_ep	*ne;

	sc->ndisusb_status |= NDISUSB_STATUS_DETACH;

	ndis_pnpevent_nic(self, NDIS_PNP_EVENT_SURPRISE_REMOVED);

	if (sc->ndisusb_status & NDISUSB_STATUS_SETUP_EP) {
		usbd_transfer_unsetup(sc->ndisusb_dread_ep.ne_xfer, 1);
		usbd_transfer_unsetup(sc->ndisusb_dwrite_ep.ne_xfer, 1);
	}
	for (i = 0; i < NDISUSB_ENDPT_MAX; i++) {
		ne = &sc->ndisusb_ep[i];
		usbd_transfer_unsetup(ne->ne_xfer, 1);
	}

	(void)ndis_detach(self);

	mtx_destroy(&sc->ndisusb_mtx);
	return (0);
}