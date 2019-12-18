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
typedef  int u_int ;
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct ofw_pci_softc {int /*<<< orphan*/  sc_pci_domain; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_RES_BUS ; 
 int RF_ACTIVE ; 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct rman* ofw_pci_get_rman (struct ofw_pci_softc*,int,int) ; 
 struct resource* pci_domain_alloc_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
ofw_pci_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct ofw_pci_softc *sc;
	struct resource *rv;
	struct rman *rm;
	int needactivate;


	needactivate = flags & RF_ACTIVE;
	flags &= ~RF_ACTIVE;

	sc = device_get_softc(bus);

#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type ==  PCI_RES_BUS) {
		  return (pci_domain_alloc_bus(sc->sc_pci_domain, child, rid,
		      start, end, count, flags | needactivate));
	}
#endif

	rm = ofw_pci_get_rman(sc, type, flags);
	if (rm == NULL)  {
		return (bus_generic_alloc_resource(bus, child, type, rid,
		    start, end, count, flags | needactivate));
	}

	rv = rman_reserve_resource(rm, start, end, count, flags, child);
	if (rv == NULL) {
		device_printf(bus, "failed to reserve resource for %s\n",
		    device_get_nameunit(child));
		return (NULL);
	}

	rman_set_rid(rv, *rid);

	if (needactivate) {
		if (bus_activate_resource(child, type, *rid, rv) != 0) {
			device_printf(bus,
			    "failed to activate resource for %s\n",
			    device_get_nameunit(child));
			rman_release_resource(rv);
			return (NULL);
		}
	}

	return (rv);
}