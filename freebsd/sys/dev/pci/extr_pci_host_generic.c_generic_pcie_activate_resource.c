#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct resource {int dummy; } ;
struct generic_pcie_core_softc {TYPE_1__* ranges; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ phys_base; scalar_t__ pci_base; } ;

/* Variables and functions */
 int BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int ENXIO ; 
 int MAX_RANGES_TUPLES ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct generic_pcie_core_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int rman_activate_resource (struct resource*) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_end (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_start (struct resource*,scalar_t__) ; 

__attribute__((used)) static int
generic_pcie_activate_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct generic_pcie_core_softc *sc;
	uint64_t phys_base;
	uint64_t pci_base;
	uint64_t size;
	int found;
	int res;
	int i;

	sc = device_get_softc(dev);

	if ((res = rman_activate_resource(r)) != 0)
		return (res);

	switch (type) {
	case SYS_RES_IOPORT:
	case SYS_RES_MEMORY:
		found = 0;
		for (i = 0; i < MAX_RANGES_TUPLES; i++) {
			pci_base = sc->ranges[i].pci_base;
			phys_base = sc->ranges[i].phys_base;
			size = sc->ranges[i].size;

			if ((rman_get_start(r) >= pci_base) && (rman_get_start(r) < (pci_base + size))) {
				found = 1;
				break;
			}
		}
		if (found) {
			rman_set_start(r, rman_get_start(r) - pci_base + phys_base);
			rman_set_end(r, rman_get_end(r) - pci_base + phys_base);
			res = BUS_ACTIVATE_RESOURCE(device_get_parent(dev),
			    child, type, rid, r);
		} else {
			device_printf(dev,
			    "Failed to activate %s resource\n",
			    type == SYS_RES_IOPORT ? "IOPORT" : "MEMORY");
			res = ENXIO;
		}
		break;
	case SYS_RES_IRQ:
		res = BUS_ACTIVATE_RESOURCE(device_get_parent(dev), child,
		    type, rid, r);
		break;
	default:
		break;
	}

	return (res);
}