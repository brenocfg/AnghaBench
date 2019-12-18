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
struct ccp_softc {int /*<<< orphan*/ * pci_resource; int /*<<< orphan*/  pci_bus_handle; int /*<<< orphan*/  pci_bus_tag; void* pci_resource_id; int /*<<< orphan*/ * pci_resource_msix; void* pci_resource_id_msix; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 struct ccp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ccp_map_pci_bar(device_t dev)
{
	struct ccp_softc *sc;

	sc = device_get_softc(dev);

	sc->pci_resource_id = PCIR_BAR(2);
	sc->pci_resource = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->pci_resource_id, RF_ACTIVE);
	if (sc->pci_resource == NULL) {
		device_printf(dev, "unable to allocate pci resource\n");
		return (ENODEV);
	}

	sc->pci_resource_id_msix = PCIR_BAR(5);
	sc->pci_resource_msix = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->pci_resource_id_msix, RF_ACTIVE);
	if (sc->pci_resource_msix == NULL) {
		device_printf(dev, "unable to allocate pci resource msix\n");
		bus_release_resource(dev, SYS_RES_MEMORY, sc->pci_resource_id,
		    sc->pci_resource);
		return (ENODEV);
	}

	sc->pci_bus_tag = rman_get_bustag(sc->pci_resource);
	sc->pci_bus_handle = rman_get_bushandle(sc->pci_resource);
	return (0);
}