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
struct arm_gic_fdt_softc {int /*<<< orphan*/  size_cells; int /*<<< orphan*/  addr_cells; } ;
struct TYPE_3__ {int /*<<< orphan*/  obd_name; } ;
struct arm_gic_devinfo {TYPE_1__ obdinfo; int /*<<< orphan*/  rl; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ arm_gic_fill_ranges (scalar_t__,struct arm_gic_fdt_softc*) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct arm_gic_fdt_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct arm_gic_devinfo*) ; 
 int /*<<< orphan*/  free (struct arm_gic_devinfo*,int /*<<< orphan*/ ) ; 
 struct arm_gic_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_1__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
arm_gic_add_children(device_t dev)
{
	struct arm_gic_fdt_softc *sc;
	struct arm_gic_devinfo *dinfo;
	phandle_t child, node;
	device_t cdev;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	/* If we have no children don't probe for them */
	child = OF_child(node);
	if (child == 0)
		return (false);

	if (arm_gic_fill_ranges(node, sc) < 0) {
		device_printf(dev, "Have a child, but no ranges\n");
		return (false);
	}

	for (; child != 0; child = OF_peer(child)) {
		dinfo = malloc(sizeof(*dinfo), M_DEVBUF, M_WAITOK | M_ZERO);

		if (ofw_bus_gen_setup_devinfo(&dinfo->obdinfo, child) != 0) {
			free(dinfo, M_DEVBUF);
			continue;
		}

		resource_list_init(&dinfo->rl);
		ofw_bus_reg_to_rl(dev, child, sc->addr_cells,
		    sc->size_cells, &dinfo->rl);

		cdev = device_add_child(dev, NULL, -1);
		if (cdev == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    dinfo->obdinfo.obd_name);
			resource_list_free(&dinfo->rl);
			ofw_bus_gen_destroy_devinfo(&dinfo->obdinfo);
			free(dinfo, M_DEVBUF);
			continue;
		}
		device_set_ivars(cdev, dinfo);
	}

	return (true);
}