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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int* sc_hub_idata; int sc_noport; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ohci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  OHCI_RH_PORT_STATUS (int) ; 
 int /*<<< orphan*/  OHCI_RH_STATUS ; 
 int OREAD4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uhub_root_intr (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
ohci_root_intr(ohci_softc_t *sc)
{
	uint32_t hstatus;
	uint16_t i;
	uint16_t m;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	/* clear any old interrupt data */
	memset(sc->sc_hub_idata, 0, sizeof(sc->sc_hub_idata));

	hstatus = OREAD4(sc, OHCI_RH_STATUS);
	DPRINTF("sc=%p hstatus=0x%08x\n",
	    sc, hstatus);

	/* set bits */
	m = (sc->sc_noport + 1);
	if (m > (8 * sizeof(sc->sc_hub_idata))) {
		m = (8 * sizeof(sc->sc_hub_idata));
	}
	for (i = 1; i < m; i++) {
		/* pick out CHANGE bits from the status register */
		if (OREAD4(sc, OHCI_RH_PORT_STATUS(i)) >> 16) {
			sc->sc_hub_idata[i / 8] |= 1 << (i % 8);
			DPRINTF("port %d changed\n", i);
		}
	}

	uhub_root_intr(&sc->sc_bus, sc->sc_hub_idata,
	    sizeof(sc->sc_hub_idata));
}