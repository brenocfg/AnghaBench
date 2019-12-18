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
struct acpi_ec_softc {int /*<<< orphan*/  ec_sci_pend; } ;

/* Variables and functions */
 int /*<<< orphan*/  EcGpeQueryHandlerSub (struct acpi_ec_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atomic_cmpset_int (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
EcGpeQueryHandler(void *Context)
{
    struct acpi_ec_softc *sc = (struct acpi_ec_softc *)Context;
    int pending;

    KASSERT(Context != NULL, ("EcGpeQueryHandler called with NULL"));

    do {
	/* Read the current pending count */
	pending = atomic_load_acq_int(&sc->ec_sci_pend);

	/* Call GPE handler function */
	EcGpeQueryHandlerSub(sc);

	/*
	 * Try to reset the pending count to zero. If this fails we
	 * know another GPE event has occurred while handling the
	 * current GPE event and need to loop.
	 */
    } while (!atomic_cmpset_int(&sc->ec_sci_pend, pending, 0));
}