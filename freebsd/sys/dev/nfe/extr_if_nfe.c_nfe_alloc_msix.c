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
struct nfe_softc {int nfe_msix; int /*<<< orphan*/ * nfe_msix_res; int /*<<< orphan*/ * nfe_msix_pba_res; int /*<<< orphan*/  nfe_dev; } ;

/* Variables and functions */
 int NFE_MSI_MESSAGES ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfe_alloc_msix(struct nfe_softc *sc, int count)
{
	int rid;

	rid = PCIR_BAR(2);
	sc->nfe_msix_res = bus_alloc_resource_any(sc->nfe_dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->nfe_msix_res == NULL) {
		device_printf(sc->nfe_dev,
		    "couldn't allocate MSIX table resource\n");
		return;
	}
	rid = PCIR_BAR(3);
	sc->nfe_msix_pba_res = bus_alloc_resource_any(sc->nfe_dev,
	    SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->nfe_msix_pba_res == NULL) {
		device_printf(sc->nfe_dev,
		    "couldn't allocate MSIX PBA resource\n");
		bus_release_resource(sc->nfe_dev, SYS_RES_MEMORY, PCIR_BAR(2),
		    sc->nfe_msix_res);
		sc->nfe_msix_res = NULL;
		return;
	}

	if (pci_alloc_msix(sc->nfe_dev, &count) == 0) {
		if (count == NFE_MSI_MESSAGES) {
			if (bootverbose)
				device_printf(sc->nfe_dev,
				    "Using %d MSIX messages\n", count);
			sc->nfe_msix = 1;
		} else {
			if (bootverbose)
				device_printf(sc->nfe_dev,
				    "couldn't allocate MSIX\n");
			pci_release_msi(sc->nfe_dev);
			bus_release_resource(sc->nfe_dev, SYS_RES_MEMORY,
			    PCIR_BAR(3), sc->nfe_msix_pba_res);
			bus_release_resource(sc->nfe_dev, SYS_RES_MEMORY,
			    PCIR_BAR(2), sc->nfe_msix_res);
			sc->nfe_msix_pba_res = NULL;
			sc->nfe_msix_res = NULL;
		}
	}
}