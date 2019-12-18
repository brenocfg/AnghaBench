#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sc_tmo_poll; int /*<<< orphan*/  sc_tmo_pcd; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EHCI_USBINTR ; 
 int /*<<< orphan*/  EOWRITE4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ ehci_hcreset (TYPE_1__*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

void
ehci_detach(ehci_softc_t *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);

	usb_callout_stop(&sc->sc_tmo_pcd);
	usb_callout_stop(&sc->sc_tmo_poll);

	EOWRITE4(sc, EHCI_USBINTR, 0);
	USB_BUS_UNLOCK(&sc->sc_bus);

	if (ehci_hcreset(sc)) {
		DPRINTF("reset failed!\n");
	}

	/* XXX let stray task complete */
	usb_pause_mtx(NULL, hz / 20);

	usb_callout_drain(&sc->sc_tmo_pcd);
	usb_callout_drain(&sc->sc_tmo_poll);
}