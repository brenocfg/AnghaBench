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
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCI_RES_BUS ; 
 int RF_ACTIVE ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct rman* ofw_pci_get_rman (struct ofw_pci_softc*,int,int) ; 
 int pci_domain_adjust_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
ofw_pci_adjust_resource(device_t bus, device_t child, int type,
    struct resource *res, rman_res_t start, rman_res_t end)
{
	struct rman *rm;
	struct ofw_pci_softc *sc;

	sc = device_get_softc(bus);
#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type == PCI_RES_BUS)
		return (pci_domain_adjust_bus(sc->sc_pci_domain, child, res,
		    start, end));
#endif

	rm = ofw_pci_get_rman(sc, type, rman_get_flags(res));
	if (rm == NULL) {
		return (bus_generic_adjust_resource(bus, child, type, res,
		    start, end));
	}
	KASSERT(rman_is_region_manager(res, rm), ("rman mismatch"));
	KASSERT(!(rman_get_flags(res) & RF_ACTIVE),
	    ("active resources cannot be adjusted"));

	return (rman_adjust_resource(res, start, end));
}