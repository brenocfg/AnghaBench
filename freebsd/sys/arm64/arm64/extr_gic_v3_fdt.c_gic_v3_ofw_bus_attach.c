#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gic_v3_softc {int /*<<< orphan*/  gic_nchildren; } ;
struct TYPE_5__ {int /*<<< orphan*/  obd_name; } ;
struct TYPE_4__ {int gic_domain; } ;
struct gic_v3_ofw_devinfo {TYPE_2__ di_dinfo; int /*<<< orphan*/  di_rl; TYPE_1__ di_gic_dinfo; } ;
typedef  int /*<<< orphan*/  size_cells ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  addr_cells ;

/* Variables and functions */
 int /*<<< orphan*/  M_GIC_V3 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct gic_v3_ofw_devinfo*) ; 
 int /*<<< orphan*/  free (struct gic_v3_ofw_devinfo*,int /*<<< orphan*/ ) ; 
 struct gic_v3_ofw_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_2__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gic_v3_ofw_bus_attach(device_t dev)
{
	struct gic_v3_ofw_devinfo *di;
	struct gic_v3_softc *sc;
	device_t child;
	phandle_t parent, node;
	pcell_t addr_cells, size_cells;

	sc = device_get_softc(dev);
	parent = ofw_bus_get_node(dev);
	if (parent > 0) {
		addr_cells = 2;
		OF_getencprop(parent, "#address-cells", &addr_cells,
		    sizeof(addr_cells));
		size_cells = 2;
		OF_getencprop(parent, "#size-cells", &size_cells,
		    sizeof(size_cells));
		/* Iterate through all GIC subordinates */
		for (node = OF_child(parent); node > 0; node = OF_peer(node)) {
			/* Allocate and populate devinfo. */
			di = malloc(sizeof(*di), M_GIC_V3, M_WAITOK | M_ZERO);

			/* Read the numa node, or -1 if there is none */
			if (OF_getencprop(node, "numa-node-id",
			    &di->di_gic_dinfo.gic_domain,
			    sizeof(di->di_gic_dinfo.gic_domain)) <= 0) {
				di->di_gic_dinfo.gic_domain = -1;
			}

			if (ofw_bus_gen_setup_devinfo(&di->di_dinfo, node)) {
				if (bootverbose) {
					device_printf(dev,
					    "Could not set up devinfo for ITS\n");
				}
				free(di, M_GIC_V3);
				continue;
			}

			/* Initialize and populate resource list. */
			resource_list_init(&di->di_rl);
			ofw_bus_reg_to_rl(dev, node, addr_cells, size_cells,
			    &di->di_rl);

			/* Should not have any interrupts, so don't add any */

			/* Add newbus device for this FDT node */
			child = device_add_child(dev, NULL, -1);
			if (!child) {
				if (bootverbose) {
					device_printf(dev,
					    "Could not add child: %s\n",
					    di->di_dinfo.obd_name);
				}
				resource_list_free(&di->di_rl);
				ofw_bus_gen_destroy_devinfo(&di->di_dinfo);
				free(di, M_GIC_V3);
				continue;
			}

			sc->gic_nchildren++;
			device_set_ivars(child, di);
		}
	}

	return (bus_generic_attach(dev));
}