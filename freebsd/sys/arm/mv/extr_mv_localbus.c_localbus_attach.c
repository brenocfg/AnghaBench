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
struct localbus_softc {int /*<<< orphan*/  sc_banks; int /*<<< orphan*/ * sc_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  obd_name; } ;
struct localbus_devinfo {TYPE_1__ di_ofw; int /*<<< orphan*/  di_res; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOCALBUS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct localbus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct localbus_devinfo*) ; 
 scalar_t__ fdt_localbus_reg_decode (scalar_t__,struct localbus_softc*,struct localbus_devinfo*) ; 
 int /*<<< orphan*/  free (struct localbus_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  localbus_banks ; 
 struct localbus_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_fdt_pm (scalar_t__) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_1__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (scalar_t__) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
localbus_attach(device_t dev)
{
	device_t dev_child;
	struct localbus_softc *sc;
	struct localbus_devinfo *di;
	phandle_t dt_node, dt_child;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_banks = localbus_banks;

	/*
	 * Walk localbus and add direct subordinates as our children.
	 */
	dt_node = ofw_bus_get_node(dev);
	for (dt_child = OF_child(dt_node); dt_child != 0;
	    dt_child = OF_peer(dt_child)) {

		/* Check and process 'status' property. */
		if (!(ofw_bus_node_status_okay(dt_child)))
			continue;

		if (!(mv_fdt_pm(dt_child)))
			continue;

		di = malloc(sizeof(*di), M_LOCALBUS, M_WAITOK | M_ZERO);
		if (ofw_bus_gen_setup_devinfo(&di->di_ofw, dt_child) != 0) {
			free(di, M_LOCALBUS);
			device_printf(dev, "could not set up devinfo\n");
			continue;
		}

		resource_list_init(&di->di_res);
		if (fdt_localbus_reg_decode(dt_child, sc, di)) {
			device_printf(dev, "could not process 'reg' "
			    "property\n");
			ofw_bus_gen_destroy_devinfo(&di->di_ofw);
			free(di, M_LOCALBUS);
			continue;
		}

		/* Add newbus device for this FDT node */
		dev_child = device_add_child(dev, NULL, -1);
		if (dev_child == NULL) {
			device_printf(dev, "could not add child: %s\n",
			    di->di_ofw.obd_name);
			resource_list_free(&di->di_res);
			ofw_bus_gen_destroy_devinfo(&di->di_ofw);
			free(di, M_LOCALBUS);
			continue;
		}
#ifdef DEBUG
		device_printf(dev, "added child: %s\n\n", di->di_ofw.obd_name);
#endif
		device_set_ivars(dev_child, di);
	}

	return (bus_generic_attach(dev));
}