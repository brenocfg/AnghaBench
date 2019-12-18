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
struct TYPE_5__ {int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_1__ ohci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  ohci_controller_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_do_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_dumpregs (TYPE_1__*) ; 
 int ohcidebug ; 

__attribute__((used)) static void
ohci_resume(ohci_softc_t *sc)
{
	DPRINTF("\n");

#ifdef USB_DEBUG
	if (ohcidebug > 2)
		ohci_dumpregs(sc);
#endif

	/* some broken BIOSes never initialize the Controller chip */
	ohci_controller_init(sc, 0);

	/* catch any lost interrupts */
	ohci_do_poll(&sc->sc_bus);
}