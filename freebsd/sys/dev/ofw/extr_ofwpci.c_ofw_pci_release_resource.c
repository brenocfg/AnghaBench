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
struct ofw_pci_softc {int /*<<< orphan*/  sc_pci_domain; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PCI_RES_BUS ; 
 int RF_ACTIVE ; 
 int bus_deactivate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_generic_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct rman* ofw_pci_get_rman (struct ofw_pci_softc*,int,int) ; 
 int pci_domain_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
ofw_pci_release_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	struct ofw_pci_softc *sc;
	struct rman *rm;
	int error;

	sc = device_get_softc(bus);

#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type == PCI_RES_BUS)
		return (pci_domain_release_bus(sc->sc_pci_domain, child, rid,
		    res));
#endif

	rm = ofw_pci_get_rman(sc, type, rman_get_flags(res));
	if (rm == NULL) {
		return (bus_generic_release_resource(bus, child, type, rid,
		    res));
	}
	KASSERT(rman_is_region_manager(res, rm), ("rman mismatch"));

	if (rman_get_flags(res) & RF_ACTIVE) {
		error = bus_deactivate_resource(child, type, rid, res);
		if (error != 0)
			return (error);
	}
	return (rman_release_resource(res));
}