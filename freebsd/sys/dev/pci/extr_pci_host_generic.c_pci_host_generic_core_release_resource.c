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
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct generic_pcie_core_softc {int /*<<< orphan*/  ecam; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PCI_RES_BUS ; 
 int bus_generic_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct generic_pcie_core_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct rman* generic_pcie_rman (struct generic_pcie_core_softc*,int) ; 
 int pci_domain_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 

int
pci_host_generic_core_release_resource(device_t dev, device_t child, int type,
    int rid, struct resource *res)
{
	struct generic_pcie_core_softc *sc;
	struct rman *rm;

	sc = device_get_softc(dev);

#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type == PCI_RES_BUS) {
		return (pci_domain_release_bus(sc->ecam, child, rid, res));
	}
#endif

	rm = generic_pcie_rman(sc, type);
	if (rm != NULL) {
		KASSERT(rman_is_region_manager(res, rm), ("rman mismatch"));
		rman_release_resource(res);
	}

	return (bus_generic_release_resource(dev, child, type, rid, res));
}