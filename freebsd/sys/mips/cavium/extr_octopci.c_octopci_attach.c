#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* rm_descr; void* rm_type; } ;
struct octopci_softc {int sc_bus; scalar_t__ sc_mem1_next; scalar_t__ sc_io_next; TYPE_1__ sc_mem1; TYPE_1__ sc_io; void* sc_mem1_base; void* sc_io_base; scalar_t__ sc_domain; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* CVMX_ADDR_DID (int /*<<< orphan*/ ) ; 
 void* CVMX_ADD_IO_SEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_FULL_DID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_OCT_DID_PCI ; 
 scalar_t__ CVMX_OCT_PCI_IO_BASE ; 
 scalar_t__ CVMX_OCT_PCI_IO_SIZE ; 
 scalar_t__ CVMX_OCT_PCI_MEM1_BASE ; 
 scalar_t__ CVMX_OCT_PCI_MEM1_SIZE ; 
 int /*<<< orphan*/  CVMX_OCT_SUBDID_PCI_IO ; 
 int /*<<< orphan*/  CVMX_OCT_SUBDID_PCI_MEM1 ; 
 int ENXIO ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PCIE ; 
 int /*<<< orphan*/  PCIR_SUBBUS_1 ; 
 void* RMAN_ARRAY ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_get_io_base_address (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_pcie_get_mem_base_address (scalar_t__) ; 
 int cvmx_pcie_rc_initialize (scalar_t__) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct octopci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 unsigned int octopci_init_bus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octopci_init_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octopci_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
octopci_attach(device_t dev)
{
	struct octopci_softc *sc;
	unsigned subbus;
	int error;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
		sc->sc_domain = device_get_unit(dev);

		error = cvmx_pcie_rc_initialize(sc->sc_domain);
		if (error != 0) {
			device_printf(dev, "Failed to put PCIe bus in host mode.\n");
			return (ENXIO);
		}

		/*
		 * In RC mode, the Simple Executive programs the first bus to
		 * be numbered as bus 1, because some IDT bridges used in
		 * Octeon systems object to being attached to bus 0.
		 */
		sc->sc_bus = 1;

		sc->sc_io_base = CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(sc->sc_domain));
		sc->sc_io.rm_descr = "Cavium Octeon PCIe I/O Ports";

		sc->sc_mem1_base = CVMX_ADD_IO_SEG(cvmx_pcie_get_mem_base_address(sc->sc_domain));
		sc->sc_mem1.rm_descr = "Cavium Octeon PCIe Memory";
	} else {
		octopci_init_pci(dev);

		sc->sc_domain = 0;
		sc->sc_bus = 0;

		sc->sc_io_base = CVMX_ADDR_DID(CVMX_FULL_DID(CVMX_OCT_DID_PCI, CVMX_OCT_SUBDID_PCI_IO));
		sc->sc_io.rm_descr = "Cavium Octeon PCI I/O Ports";

		sc->sc_mem1_base = CVMX_ADDR_DID(CVMX_FULL_DID(CVMX_OCT_DID_PCI, CVMX_OCT_SUBDID_PCI_MEM1));
		sc->sc_mem1.rm_descr = "Cavium Octeon PCI Memory";
	}

	sc->sc_io.rm_type = RMAN_ARRAY;
	error = rman_init(&sc->sc_io);
	if (error != 0)
		return (error);

	error = rman_manage_region(&sc->sc_io, CVMX_OCT_PCI_IO_BASE,
	    CVMX_OCT_PCI_IO_BASE + CVMX_OCT_PCI_IO_SIZE);
	if (error != 0)
		return (error);

	sc->sc_mem1.rm_type = RMAN_ARRAY;
	error = rman_init(&sc->sc_mem1);
	if (error != 0)
		return (error);

	error = rman_manage_region(&sc->sc_mem1, CVMX_OCT_PCI_MEM1_BASE,
	    CVMX_OCT_PCI_MEM1_BASE + CVMX_OCT_PCI_MEM1_SIZE);
	if (error != 0)
		return (error);

	/*
	 * Next offsets for resource allocation in octopci_init_bar.
	 */
	sc->sc_io_next = 0;
	sc->sc_mem1_next = 0;

	/*
	 * Configure devices.
	 */
	octopci_write_config(dev, sc->sc_bus, 0, 0, PCIR_SUBBUS_1, 0xff, 1);
	subbus = octopci_init_bus(dev, sc->sc_bus);
	octopci_write_config(dev, sc->sc_bus, 0, 0, PCIR_SUBBUS_1, subbus, 1);

	device_add_child(dev, "pci", -1);

	return (bus_generic_attach(dev));
}