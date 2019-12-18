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
struct TYPE_5__ {int* sc_hub_idata; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  sc_root_intr; } ;
typedef  TYPE_1__ uhci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UHCI_PORTSC1 ; 
 int /*<<< orphan*/  UHCI_PORTSC2 ; 
 int UHCI_PORTSC_CSC ; 
 int UHCI_PORTSC_OCIC ; 
 int UHCI_PORTSC_RD ; 
 int UREAD2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  uhub_root_intr (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_1__*) ; 

__attribute__((used)) static void
uhci_root_intr(uhci_softc_t *sc)
{
	DPRINTFN(21, "\n");

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	sc->sc_hub_idata[0] = 0;

	if (UREAD2(sc, UHCI_PORTSC1) & (UHCI_PORTSC_CSC |
	    UHCI_PORTSC_OCIC | UHCI_PORTSC_RD)) {
		sc->sc_hub_idata[0] |= 1 << 1;
	}
	if (UREAD2(sc, UHCI_PORTSC2) & (UHCI_PORTSC_CSC |
	    UHCI_PORTSC_OCIC | UHCI_PORTSC_RD)) {
		sc->sc_hub_idata[0] |= 1 << 2;
	}

	/* restart timer */
	usb_callout_reset(&sc->sc_root_intr, hz,
	    (void *)&uhci_root_intr, sc);

	if (sc->sc_hub_idata[0] != 0) {
		uhub_root_intr(&sc->sc_bus, sc->sc_hub_idata,
		    sizeof(sc->sc_hub_idata));
	}
}