#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int* sc_hub_idata; int sc_noport; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  EHCI_PORTSC (int) ; 
 int EHCI_PS_CLEAR ; 
 int EOREAD4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uhub_root_intr (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
ehci_root_intr(ehci_softc_t *sc)
{
	uint16_t i;
	uint16_t m;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	/* clear any old interrupt data */
	memset(sc->sc_hub_idata, 0, sizeof(sc->sc_hub_idata));

	/* set bits */
	m = (sc->sc_noport + 1);
	if (m > (8 * sizeof(sc->sc_hub_idata))) {
		m = (8 * sizeof(sc->sc_hub_idata));
	}
	for (i = 1; i < m; i++) {
		/* pick out CHANGE bits from the status register */
		if (EOREAD4(sc, EHCI_PORTSC(i)) & EHCI_PS_CLEAR) {
			sc->sc_hub_idata[i / 8] |= 1 << (i % 8);
			DPRINTF("port %d changed\n", i);
		}
	}
	uhub_root_intr(&sc->sc_bus, sc->sc_hub_idata,
	    sizeof(sc->sc_hub_idata));
}