#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int ecam; scalar_t__ coherent; int bus_end; int /*<<< orphan*/  mem_rman; int /*<<< orphan*/  io_rman; TYPE_1__* ranges; scalar_t__ bus_start; } ;
struct generic_pcie_fdt_softc {int /*<<< orphan*/  pci_iinfo; TYPE_2__ base; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell_t ;
struct TYPE_3__ {scalar_t__ phys_base; scalar_t__ pci_base; scalar_t__ size; int flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int FLAG_IO ; 
 int FLAG_MEM ; 
 int MAX_RANGES_TUPLES ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PCI_IO_WINDOW_OFFSET ; 
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct generic_pcie_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ generic_pcie_ofw_bus_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_setup_iinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ parse_pci_mem_ranges (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int pci_host_generic_core_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 
 int rman_manage_region (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

int
pci_host_generic_attach(device_t dev)
{
	struct generic_pcie_fdt_softc *sc;
	uint64_t phys_base;
	uint64_t pci_base;
	uint64_t size;
	phandle_t node;
	int error;
	int tuple;

	sc = device_get_softc(dev);

	/* Retrieve 'ranges' property from FDT */
	if (bootverbose)
		device_printf(dev, "parsing FDT for ECAM%d:\n", sc->base.ecam);
	if (parse_pci_mem_ranges(dev, &sc->base))
		return (ENXIO);

	/* Attach OFW bus */
	if (generic_pcie_ofw_bus_attach(dev) != 0)
		return (ENXIO);

	node = ofw_bus_get_node(dev);
	if (sc->base.coherent == 0) {
		sc->base.coherent = OF_hasprop(node, "dma-coherent");
	}
	if (bootverbose)
		device_printf(dev, "Bus is%s cache-coherent\n",
		    sc->base.coherent ? "" : " not");

	/* TODO parse FDT bus ranges */
	sc->base.bus_start = 0;
	sc->base.bus_end = 0xFF;
	error = pci_host_generic_core_attach(dev);
	if (error != 0)
		return (error);

	for (tuple = 0; tuple < MAX_RANGES_TUPLES; tuple++) {
		phys_base = sc->base.ranges[tuple].phys_base;
		pci_base = sc->base.ranges[tuple].pci_base;
		size = sc->base.ranges[tuple].size;
		if (phys_base == 0 || size == 0)
			continue; /* empty range element */
		if (sc->base.ranges[tuple].flags & FLAG_MEM) {
			error = rman_manage_region(&sc->base.mem_rman,
			    pci_base, pci_base + size - 1);
		} else if (sc->base.ranges[tuple].flags & FLAG_IO) {
			error = rman_manage_region(&sc->base.io_rman,
			    pci_base + PCI_IO_WINDOW_OFFSET,
			    pci_base + PCI_IO_WINDOW_OFFSET + size - 1);
		} else
			continue;
		if (error) {
			device_printf(dev, "rman_manage_region() failed."
						"error = %d\n", error);
			rman_fini(&sc->base.mem_rman);
			return (error);
		}
	}

	ofw_bus_setup_iinfo(node, &sc->pci_iinfo, sizeof(cell_t));

	device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}