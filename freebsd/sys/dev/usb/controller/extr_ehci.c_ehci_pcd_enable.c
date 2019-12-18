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
typedef  TYPE_1__ ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_STS_PCD ; 
 int /*<<< orphan*/  EHCI_USBINTR ; 
 int /*<<< orphan*/  EHCI_USBSTS ; 
 int /*<<< orphan*/  EOWRITE4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_root_intr (TYPE_1__*) ; 

__attribute__((used)) static void
ehci_pcd_enable(ehci_softc_t *sc)
{
	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	sc->sc_eintrs |= EHCI_STS_PCD;
	EOWRITE4(sc, EHCI_USBINTR, sc->sc_eintrs);

	/* acknowledge any PCD interrupt */
	EOWRITE4(sc, EHCI_USBSTS, EHCI_STS_PCD);

	ehci_root_intr(sc);
}