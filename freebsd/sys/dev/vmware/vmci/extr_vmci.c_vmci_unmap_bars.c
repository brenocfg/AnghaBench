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
struct vmci_softc {int /*<<< orphan*/ * vmci_res1; int /*<<< orphan*/  vmci_dev; int /*<<< orphan*/ * vmci_res0; } ;

/* Variables and functions */
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmci_unmap_bars(struct vmci_softc *sc)
{
	int rid;

	if (sc->vmci_res0 != NULL) {
		rid = PCIR_BAR(0);
		bus_release_resource(sc->vmci_dev, SYS_RES_IOPORT, rid,
		    sc->vmci_res0);
		sc->vmci_res0 = NULL;
	}

	if (sc->vmci_res1 != NULL) {
		rid = PCIR_BAR(1);
		bus_release_resource(sc->vmci_dev, SYS_RES_MEMORY, rid,
		    sc->vmci_res1);
		sc->vmci_res1 = NULL;
	}
}