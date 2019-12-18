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
struct vtpci_softc {int /*<<< orphan*/ * vtpci_res; int /*<<< orphan*/ * vtpci_msix_res; int /*<<< orphan*/ * vtpci_child_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_reset (struct vtpci_softc*) ; 

__attribute__((used)) static int
vtpci_detach(device_t dev)
{
	struct vtpci_softc *sc;
	device_t child;
	int error;

	sc = device_get_softc(dev);

	if ((child = sc->vtpci_child_dev) != NULL) {
		error = device_delete_child(dev, child);
		if (error)
			return (error);
		sc->vtpci_child_dev = NULL;
	}

	vtpci_reset(sc);

	if (sc->vtpci_msix_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(1),
		    sc->vtpci_msix_res);
		sc->vtpci_msix_res = NULL;
	}

	if (sc->vtpci_res != NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT, PCIR_BAR(0),
		    sc->vtpci_res);
		sc->vtpci_res = NULL;
	}

	return (0);
}