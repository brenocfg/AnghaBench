#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_4__ {char* rm_descr; void* rm_type; } ;
struct ofw_pci_softc {int sc_initialized; int sc_quirks; int sc_nrange; int sc_range_mask; int sc_have_pmem; TYPE_1__ sc_pmem_rman; TYPE_1__ sc_mem_rman; TYPE_1__ sc_io_rman; struct ofw_pci_range* sc_range; int /*<<< orphan*/  sc_pci_iinfo; scalar_t__ sc_bus; scalar_t__ sc_node; int /*<<< orphan*/  sc_dev; struct ofw_pci_range* sc_cell_info; int /*<<< orphan*/  sc_pci_domain; } ;
struct ofw_pci_range {int pci_hi; scalar_t__ size; scalar_t__ pci; } ;
struct ofw_pci_cell_info {int pci_hi; scalar_t__ size; scalar_t__ pci; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell_t ;
typedef  int /*<<< orphan*/  busrange ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OFW_PCI_PHYS_HI_PREFETCHABLE ; 
 int OFW_PCI_PHYS_HI_SPACEMASK ; 
#define  OFW_PCI_PHYS_HI_SPACE_CONFIG 131 
#define  OFW_PCI_PHYS_HI_SPACE_IO 130 
#define  OFW_PCI_PHYS_HI_SPACE_MEM32 129 
#define  OFW_PCI_PHYS_HI_SPACE_MEM64 128 
 int OFW_PCI_QUIRK_RANGES_ON_CHILDREN ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 void* RMAN_ARRAY ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct ofw_pci_range*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_setup_iinfo (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int ofw_pci_fill_ranges (scalar_t__,struct ofw_pci_range*) ; 
 void* ofw_pci_nranges (scalar_t__,struct ofw_pci_range*) ; 
 int /*<<< orphan*/  rman_fini (TYPE_1__*) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

int
ofw_pci_init(device_t dev)
{
	struct ofw_pci_softc *sc;
	phandle_t node;
	u_int32_t busrange[2];
	struct ofw_pci_range *rp;
	int i, error;
	struct ofw_pci_cell_info *cell_info;

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);
	sc->sc_initialized = 1;
	sc->sc_range = NULL;
	sc->sc_pci_domain = device_get_unit(dev);

	cell_info = (struct ofw_pci_cell_info *)malloc(sizeof(*cell_info),
	    M_DEVBUF, M_WAITOK | M_ZERO);

	sc->sc_cell_info = cell_info;

	if (OF_getencprop(node, "bus-range", busrange, sizeof(busrange)) != 8)
		busrange[0] = 0;

	sc->sc_dev = dev;
	sc->sc_node = node;
	sc->sc_bus = busrange[0];

	if (sc->sc_quirks & OFW_PCI_QUIRK_RANGES_ON_CHILDREN) {
		phandle_t c;
		int n, i;

		sc->sc_nrange = 0;
		for (c = OF_child(node); c != 0; c = OF_peer(c)) {
			n = ofw_pci_nranges(c, cell_info);
			if (n > 0)
				sc->sc_nrange += n;
		}
		if (sc->sc_nrange == 0) {
			error = ENXIO;
			goto out;
		}
		sc->sc_range = malloc(sc->sc_nrange * sizeof(sc->sc_range[0]),
		    M_DEVBUF, M_WAITOK);
		i = 0;
		for (c = OF_child(node); c != 0; c = OF_peer(c)) {
			n = ofw_pci_fill_ranges(c, &sc->sc_range[i]);
			if (n > 0)
				i += n;
		}
		KASSERT(i == sc->sc_nrange, ("range count mismatch"));
	} else {
		sc->sc_nrange = ofw_pci_nranges(node, cell_info);
		if (sc->sc_nrange <= 0) {
			device_printf(dev, "could not getranges\n");
			error = ENXIO;
			goto out;
		}
		sc->sc_range = malloc(sc->sc_nrange * sizeof(sc->sc_range[0]),
		    M_DEVBUF, M_WAITOK);
		ofw_pci_fill_ranges(node, sc->sc_range);
	}

	sc->sc_io_rman.rm_type = RMAN_ARRAY;
	sc->sc_io_rman.rm_descr = "PCI I/O Ports";
	error = rman_init(&sc->sc_io_rman);
	if (error != 0) {
		device_printf(dev, "rman_init() failed. error = %d\n", error);
		goto out;
	}

	sc->sc_mem_rman.rm_type = RMAN_ARRAY;
	sc->sc_mem_rman.rm_descr = "PCI Non Prefetchable Memory";
	error = rman_init(&sc->sc_mem_rman);
	if (error != 0) {
		device_printf(dev, "rman_init() failed. error = %d\n", error);
		goto out;
	}

	sc->sc_pmem_rman.rm_type = RMAN_ARRAY;
	sc->sc_pmem_rman.rm_descr = "PCI Prefetchable Memory";
	error = rman_init(&sc->sc_pmem_rman);
	if (error != 0) {
		device_printf(dev, "rman_init() failed. error = %d\n", error);
		goto out;
	}

	for (i = 0; i < sc->sc_nrange; i++) {
		error = 0;
		rp = sc->sc_range + i;

		if (sc->sc_range_mask & ((uint64_t)1 << i))
			continue;
		switch (rp->pci_hi & OFW_PCI_PHYS_HI_SPACEMASK) {
		case OFW_PCI_PHYS_HI_SPACE_CONFIG:
			break;
		case OFW_PCI_PHYS_HI_SPACE_IO:
			error = rman_manage_region(&sc->sc_io_rman, rp->pci,
			    rp->pci + rp->size - 1);
			break;
		case OFW_PCI_PHYS_HI_SPACE_MEM32:
		case OFW_PCI_PHYS_HI_SPACE_MEM64:
			if (rp->pci_hi & OFW_PCI_PHYS_HI_PREFETCHABLE) {
				sc->sc_have_pmem = 1;
				error = rman_manage_region(&sc->sc_pmem_rman,
				    rp->pci, rp->pci + rp->size - 1);
			} else {
				error = rman_manage_region(&sc->sc_mem_rman,
				    rp->pci, rp->pci + rp->size - 1);
			}
			break;
		}

		if (error != 0) {
			device_printf(dev,
			    "rman_manage_region(%x, %#jx, %#jx) failed. "
			    "error = %d\n", rp->pci_hi &
			    OFW_PCI_PHYS_HI_SPACEMASK, rp->pci,
			    rp->pci + rp->size - 1, error);
			goto out;
		}
	}

	ofw_bus_setup_iinfo(node, &sc->sc_pci_iinfo, sizeof(cell_t));
	return (0);

out:
	free(cell_info, M_DEVBUF);
	free(sc->sc_range, M_DEVBUF);
	rman_fini(&sc->sc_io_rman);
	rman_fini(&sc->sc_mem_rman);
	rman_fini(&sc->sc_pmem_rman);

	return (error);
}