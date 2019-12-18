#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {char* rm_descr; void* rm_type; } ;
struct ps3bus_softc {TYPE_1__ sc_mem_rman; int /*<<< orphan*/  rcount; int /*<<< orphan*/  regions; TYPE_1__ sc_intr_rman; } ;
struct ps3bus_devinfo {int bus; int dev; int bustype; int devtype; int busidx; int devidx; int /*<<< orphan*/  iommu_mtx; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_IRQ ; 
 int /*<<< orphan*/  EHCI_REG ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_PS3BUS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OHCI_IRQ ; 
 int /*<<< orphan*/  OHCI_REG ; 
 int PS3_BUSTYPE_STORAGE ; 
 int PS3_BUSTYPE_SYSBUS ; 
#define  PS3_DEVTYPE_USB 128 
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 void* RMAN_ARRAY ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 struct ps3bus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ps3bus_devinfo*) ; 
 int /*<<< orphan*/  free (struct ps3bus_devinfo*,int /*<<< orphan*/ ) ; 
 int lv1_get_repository_node_value (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  lv1_open_device (int,int,int /*<<< orphan*/ ) ; 
 int lv1_repository_string (char*) ; 
 struct ps3bus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mem_regions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3bus_resources_init (TYPE_1__*,int,int,struct ps3bus_devinfo*) ; 
 int /*<<< orphan*/  ps3bus_resources_init_by_type (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ps3bus_devinfo*) ; 
 int /*<<< orphan*/  rman_init (TYPE_1__*) ; 
 int /*<<< orphan*/  rman_manage_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
ps3bus_attach(device_t self) 
{
	struct ps3bus_softc *sc;
	struct ps3bus_devinfo *dinfo;
	int bus_index, dev_index, result;
	uint64_t bustype, bus, devs;
	uint64_t dev, devtype;
	uint64_t junk;
	device_t cdev;

	sc = device_get_softc(self);
	sc->sc_mem_rman.rm_type = RMAN_ARRAY;
	sc->sc_mem_rman.rm_descr = "PS3Bus Memory Mapped I/O";
	sc->sc_intr_rman.rm_type = RMAN_ARRAY;
	sc->sc_intr_rman.rm_descr = "PS3Bus Interrupts";
	rman_init(&sc->sc_mem_rman);
	rman_init(&sc->sc_intr_rman);
	rman_manage_region(&sc->sc_intr_rman, 0, ~0);

	/* Get memory regions for DMA */
	mem_regions(&sc->regions, &sc->rcount, NULL, NULL);

	/*
	 * Probe all the PS3's buses.
	 */

	for (bus_index = 0; bus_index < 5; bus_index++) {
		result = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
		    (lv1_repository_string("bus") >> 32) | bus_index,
		    lv1_repository_string("type"), 0, 0, &bustype, &junk);

		if (result != 0)
			continue;

		result = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
		    (lv1_repository_string("bus") >> 32) | bus_index,
		    lv1_repository_string("id"), 0, 0, &bus, &junk);

		if (result != 0)
			continue;

		result = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
		    (lv1_repository_string("bus") >> 32) | bus_index,
		    lv1_repository_string("num_dev"), 0, 0, &devs, &junk);

		for (dev_index = 0; dev_index < devs; dev_index++) {
			result = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
			    (lv1_repository_string("bus") >> 32) | bus_index,
			    lv1_repository_string("dev") | dev_index,
			    lv1_repository_string("type"), 0, &devtype, &junk);

			if (result != 0)
				continue;

			result = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
			    (lv1_repository_string("bus") >> 32) | bus_index,
			    lv1_repository_string("dev") | dev_index,
			    lv1_repository_string("id"), 0, &dev, &junk);

			if (result != 0)
				continue;
			
			switch (devtype) {
			case PS3_DEVTYPE_USB:
				/* USB device has OHCI and EHCI USB host controllers */

				lv1_open_device(bus, dev, 0);

				/* OHCI host controller */

				dinfo = malloc(sizeof(*dinfo), M_PS3BUS,
				    M_WAITOK | M_ZERO);

				dinfo->bus = bus;
				dinfo->dev = dev;
				dinfo->bustype = bustype;
				dinfo->devtype = devtype;
				dinfo->busidx = bus_index;
				dinfo->devidx = dev_index;

				ps3bus_resources_init_by_type(&sc->sc_mem_rman, bus_index,
				    dev_index, OHCI_IRQ, OHCI_REG, dinfo);

				cdev = device_add_child(self, "ohci", -1);
				if (cdev == NULL) {
					device_printf(self,
					    "device_add_child failed\n");
					free(dinfo, M_PS3BUS);
					continue;
				}

				mtx_init(&dinfo->iommu_mtx, "iommu", NULL, MTX_DEF);
				device_set_ivars(cdev, dinfo);

				/* EHCI host controller */

				dinfo = malloc(sizeof(*dinfo), M_PS3BUS,
				    M_WAITOK | M_ZERO);

				dinfo->bus = bus;
				dinfo->dev = dev;
				dinfo->bustype = bustype;
				dinfo->devtype = devtype;
				dinfo->busidx = bus_index;
				dinfo->devidx = dev_index;

				ps3bus_resources_init_by_type(&sc->sc_mem_rman, bus_index,
				    dev_index, EHCI_IRQ, EHCI_REG, dinfo);

				cdev = device_add_child(self, "ehci", -1);
				if (cdev == NULL) {
					device_printf(self,
					    "device_add_child failed\n");
					free(dinfo, M_PS3BUS);
					continue;
				}

				mtx_init(&dinfo->iommu_mtx, "iommu", NULL, MTX_DEF);
				device_set_ivars(cdev, dinfo);
				break;
			default:
				dinfo = malloc(sizeof(*dinfo), M_PS3BUS,
				    M_WAITOK | M_ZERO);

				dinfo->bus = bus;
				dinfo->dev = dev;
				dinfo->bustype = bustype;
				dinfo->devtype = devtype;
				dinfo->busidx = bus_index;
				dinfo->devidx = dev_index;

				if (dinfo->bustype == PS3_BUSTYPE_SYSBUS ||
				    dinfo->bustype == PS3_BUSTYPE_STORAGE)
					lv1_open_device(bus, dev, 0);

				ps3bus_resources_init(&sc->sc_mem_rman, bus_index,
				    dev_index, dinfo);

				cdev = device_add_child(self, NULL, -1);
				if (cdev == NULL) {
					device_printf(self,
					    "device_add_child failed\n");
					free(dinfo, M_PS3BUS);
					continue;
				}

				mtx_init(&dinfo->iommu_mtx, "iommu", NULL, MTX_DEF);
				device_set_ivars(cdev, dinfo);
			}
		}
	}
	
	clock_register(self, 1000);

	return (bus_generic_attach(self));
}