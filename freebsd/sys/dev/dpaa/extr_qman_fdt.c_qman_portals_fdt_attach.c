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
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
typedef  int uintmax_t ;
typedef  int uint32_t ;
struct ofw_bus_devinfo {int /*<<< orphan*/  obd_name; } ;
struct dpaa_portals_softc {int sc_dp_size; int sc_dp_pa; int /*<<< orphan*/  sc_dev; } ;
struct dpaa_portals_devinfo {int di_intr_rid; int /*<<< orphan*/  di_res; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ ihandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cpu_num ;
typedef  int /*<<< orphan*/  cpu ;
typedef  int cell_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 int OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,void*,int) ; 
 scalar_t__ OF_instance_to_package (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct dpaa_portals_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ dpaa_portal_alloc_res (int /*<<< orphan*/ ,struct dpaa_portals_devinfo*,int) ; 
 int /*<<< orphan*/  get_addr_props (scalar_t__,int*,int*) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (struct ofw_bus_devinfo*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (struct ofw_bus_devinfo*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_intr_to_rl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ofw_bus_node_is_compatible (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_reg_to_rl (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ qman_portal_find_cpu (int) ; 
 int qman_portals_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qman_portals_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qman_portals_fdt_attach(device_t dev)
{
	struct dpaa_portals_softc *sc;
	phandle_t node, child, cpu_node;
	vm_paddr_t portal_pa, portal_par_pa;
	vm_size_t portal_size;
	uint32_t addr, paddr, size;
	ihandle_t cpu;
	int cpu_num, cpus, intr_rid;
	struct dpaa_portals_devinfo di;
	struct ofw_bus_devinfo ofw_di = {};
	cell_t *range;
	int nrange;
	int i;

	cpus = 0;
	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	node = ofw_bus_get_node(dev);

	/* Get this node's range */
	get_addr_props(ofw_bus_get_node(device_get_parent(dev)), &paddr, &size);
	get_addr_props(node, &addr, &size);

	nrange = OF_getencprop_alloc_multi(node, "ranges",
	    sizeof(*range), (void **)&range);
	if (nrange < addr + paddr + size)
		return (ENXIO);
	portal_pa = portal_par_pa = 0;
	portal_size = 0;
	for (i = 0; i < addr; i++) {
		portal_pa <<= 32;
		portal_pa |= range[i];
	}
	for (; i < paddr + addr; i++) {
		portal_par_pa <<= 32;
		portal_par_pa |= range[i];
	}
	portal_pa += portal_par_pa;
	for (; i < size + paddr + addr; i++) {
		portal_size = (uintmax_t)portal_size << 32;
		portal_size |= range[i];
	}
	OF_prop_free(range);
	sc->sc_dp_size = portal_size;
	sc->sc_dp_pa = portal_pa;

	/* Find portals tied to CPUs */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		if (cpus >= mp_ncpus)
			break;
		if (!ofw_bus_node_is_compatible(child, "fsl,qman-portal")) {
			continue;
		}
		/* Checkout related cpu */
		if (OF_getprop(child, "cpu-handle", (void *)&cpu,
		    sizeof(cpu)) <= 0) {
			cpu = qman_portal_find_cpu(cpus);
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

		if (dpaa_portal_alloc_res(dev, &di, cpu_num))
			goto err;
	}

	ofw_bus_gen_destroy_devinfo(&ofw_di);

	return (qman_portals_attach(dev));
err:
	resource_list_free(&di.di_res);
	ofw_bus_gen_destroy_devinfo(&ofw_di);
	qman_portals_detach(dev);
	return (ENXIO);
}