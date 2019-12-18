#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_7__ {TYPE_6__ sc_bus; } ;
typedef  TYPE_1__ uhci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UHCI_INTR ; 
 int UHCI_INTR_IOCE ; 
 int UHCI_INTR_RIE ; 
 int UHCI_INTR_SPIE ; 
 int UHCI_INTR_TOCRCIE ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWRITE2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uhci_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  uhci_root_intr (TYPE_1__*) ; 

__attribute__((used)) static void
uhci_start(uhci_softc_t *sc)
{
	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	DPRINTFN(2, "enabling\n");

	/* enable interrupts */

	UWRITE2(sc, UHCI_INTR,
	    (UHCI_INTR_TOCRCIE |
	    UHCI_INTR_RIE |
	    UHCI_INTR_IOCE |
	    UHCI_INTR_SPIE));

	if (uhci_restart(sc)) {
		device_printf(sc->sc_bus.bdev,
		    "cannot start HC controller\n");
	}

	/* start root interrupt */
	uhci_root_intr(sc);
}