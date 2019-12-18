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
typedef  TYPE_1__ ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_do_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_hcreset (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_init_sub (TYPE_1__*) ; 

__attribute__((used)) static void
ehci_resume(ehci_softc_t *sc)
{
	/* reset HC */
	ehci_hcreset(sc);

	/* setup HC */
	ehci_init_sub(sc);

	/* catch any lost interrupts */
	ehci_do_poll(&sc->sc_bus);
}