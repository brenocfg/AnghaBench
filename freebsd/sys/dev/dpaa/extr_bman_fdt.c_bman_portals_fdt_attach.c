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
typedef  void* vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct resource_list_entry {scalar_t__ start; void* end; } ;
struct ofw_bus_devinfo {int /*<<< orphan*/  obd_name; } ;
struct dpaa_portals_softc {scalar_t__ sc_dp_pa; void* sc_dp_size; int /*<<< orphan*/  sc_dev; } ;
struct dpaa_portals_devinfo {int di_intr_rid; int /*<<< orphan*/  di_res; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ ihandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cpu_num ;
typedef  int /*<<< orphan*/  cpu ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,void*,int) ; 
 scalar_t__ OF_instance_to_package (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bman_portal_find_cpu (int) ; 
 int bman_portals_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bman_portals_detach (int /*<<< orphan*/ ) ; 
 struct dpaa_portals_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dpaa_portal_alloc_res (int /*<<< orphan*/ ,struct dpaa_portals_devinfo*,int) ; 
 int /*<<< orphan*/  get_addr_props (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (struct ofw_bus_devinfo*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (struct ofw_bus_devinfo*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_intr_to_rl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ofw_bus_node_is_compatible (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_reg_to_rl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_reg_to_paddr (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,void**,int /*<<< orphan*/ *) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 void* ulmax (void*,void*) ; 

__attribute__((used)) static int
bman_portals_fdt_attach(device_t dev)
{
	struct dpaa_portals_softc *sc;
	struct resource_list_entry *rle;
	phandle_t node, child, cpu_node;
	vm_paddr_t portal_pa;
	vm_size_t portal_size;
	uint32_t addr, size;
	ihandle_t cpu;
	int cpu_num, cpus, intr_rid;
	struct dpaa_portals_devinfo di;
	struct ofw_bus_devinfo ofw_di = {};

	cpus = 0;
	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	node = ofw_bus_get_node(dev);
	get_addr_props(node, &addr, &size);

	/* Find portals tied to CPUs */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		if (cpus >= mp_ncpus)
			break;
		if (!ofw_bus_node_is_compatible(child, "fsl,bman-portal")) {
			continue;
		}
		/* Checkout related cpu */
		if (OF_getprop(child, "cpu-handle", (void *)&cpu,
		    sizeof(cpu)) <= 0) {
			cpu = bman_portal_find_cpu(cpus);
			if (cpu <= 0)
				continue;
		}
		/* Acquire cpu number */
		cpu_node = OF_instance_to_package(cpu);
		if (OF_getencprop(cpu_node, "reg", &cpu_num, sizeof(cpu_num)) <= 0) {
			device_printf(dev, "Could not retrieve CPU number.\n");
			return (ENXIO);
		}

		cpus++;

		if (ofw_bus_gen_setup_devinfo(&ofw_di, child) != 0) {
			device_printf(dev, "could not set up devinfo\n");
			continue;
		}

		resource_list_init(&di.di_res);
		if (ofw_bus_reg_to_rl(dev, child, addr, size, &di.di_res)) {
			device_printf(dev, "%s: could not process 'reg' "
			    "property\n", ofw_di.obd_name);
			ofw_bus_gen_destroy_devinfo(&ofw_di);
			continue;
		}
		if (ofw_bus_intr_to_rl(dev, child, &di.di_res, &intr_rid)) {
			device_printf(dev, "%s: could not process "
			    "'interrupts' property\n", ofw_di.obd_name);
			resource_list_free(&di.di_res);
			ofw_bus_gen_destroy_devinfo(&ofw_di);
			continue;
		}
		di.di_intr_rid = intr_rid;
		
		ofw_reg_to_paddr(child, 0, &portal_pa, &portal_size, NULL);
		rle = resource_list_find(&di.di_res, SYS_RES_MEMORY, 0);

		if (sc->sc_dp_pa == 0)
			sc->sc_dp_pa = portal_pa - rle->start;

		portal_size = rle->end + 1;
		rle = resource_list_find(&di.di_res, SYS_RES_MEMORY, 1);
		portal_size = ulmax(rle->end + 1, portal_size);
		sc->sc_dp_size = ulmax(sc->sc_dp_size, portal_size);

		if (dpaa_portal_alloc_res(dev, &di, cpu_num))
			goto err;
	}

	ofw_bus_gen_destroy_devinfo(&ofw_di);

	return (bman_portals_attach(dev));
err:
	resource_list_free(&di.di_res);
	ofw_bus_gen_destroy_devinfo(&ofw_di);
	bman_portals_detach(dev);
	return (ENXIO);
}