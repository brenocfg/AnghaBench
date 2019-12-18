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
struct uss820dci_softc {int* sc_hub_idata; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhub_root_intr (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
uss820dci_root_intr(struct uss820dci_softc *sc)
{
	DPRINTFN(9, "\n");

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	/* set port bit */
	sc->sc_hub_idata[0] = 0x02;	/* we only have one port */

	uhub_root_intr(&sc->sc_bus, sc->sc_hub_idata,
	    sizeof(sc->sc_hub_idata));
}