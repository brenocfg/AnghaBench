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
struct ohci_softc {int /*<<< orphan*/  sc_tmo_rhsc; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_ALL_INTRS ; 
 int /*<<< orphan*/  OHCI_CONTROL ; 
 int /*<<< orphan*/  OHCI_HCFS_RESET ; 
 int /*<<< orphan*/  OHCI_INTERRUPT_DISABLE ; 
 int /*<<< orphan*/  OWRITE4 (struct ohci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

void
ohci_detach(struct ohci_softc *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);

	usb_callout_stop(&sc->sc_tmo_rhsc);

	OWRITE4(sc, OHCI_INTERRUPT_DISABLE, OHCI_ALL_INTRS);
	OWRITE4(sc, OHCI_CONTROL, OHCI_HCFS_RESET);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* XXX let stray task complete */
	usb_pause_mtx(NULL, hz / 20);

	usb_callout_drain(&sc->sc_tmo_rhsc);
}