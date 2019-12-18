#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ uhci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  UHCICMD (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UHCI_CMD_FGR ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_do_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_dumpregs (TYPE_1__*) ; 
 int /*<<< orphan*/  uhci_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  uhci_start (TYPE_1__*) ; 
 int uhcidebug ; 

__attribute__((used)) static void
uhci_resume(uhci_softc_t *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);

	/* reset the controller */

	uhci_reset(sc);

	/* force global resume */

	UHCICMD(sc, UHCI_CMD_FGR);

	/* and start traffic again */

	uhci_start(sc);

	USB_BUS_UNLOCK(&sc->sc_bus);

#ifdef USB_DEBUG
	if (uhcidebug > 2)
		uhci_dumpregs(sc);
#endif

	/* catch lost interrupts */
	uhci_do_poll(&sc->sc_bus);
}