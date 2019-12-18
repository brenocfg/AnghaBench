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
struct TYPE_5__ {int /*<<< orphan*/  sc_eintrs; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ohci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  OHCI_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  OHCI_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  OHCI_RHSC ; 
 int /*<<< orphan*/  OWRITE4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_root_intr (TYPE_1__*) ; 

__attribute__((used)) static void
ohci_rhsc_enable(ohci_softc_t *sc)
{
	DPRINTFN(5, "\n");

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	sc->sc_eintrs |= OHCI_RHSC;
	OWRITE4(sc, OHCI_INTERRUPT_ENABLE, OHCI_RHSC);

	/* acknowledge any RHSC interrupt */
	OWRITE4(sc, OHCI_INTERRUPT_STATUS, OHCI_RHSC);

	ohci_root_intr(sc);
}