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
struct simplebus_softc {int /*<<< orphan*/  scells; int /*<<< orphan*/  acells; } ;
struct mdionexus_ofw_devinfo {int /*<<< orphan*/  di_dinfo; int /*<<< orphan*/  di_rl; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_THUNDER_MDIO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct mdionexus_ofw_devinfo*) ; 
 int /*<<< orphan*/  free (struct mdionexus_ofw_devinfo*,int /*<<< orphan*/ ) ; 
 struct mdionexus_ofw_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mdionexus_ofw_fill_ranges (scalar_t__,struct simplebus_softc*) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
mdionexus_ofw_bus_attach(device_t dev)
{
	struct simplebus_softc *sc;
	struct mdionexus_ofw_devinfo *di;
	device_t child;
	phandle_t parent, node;

	parent = ofw_bus_get_node(dev);
	simplebus_init(dev, parent);

	sc = (struct simplebus_softc *)device_get_softc(dev);

	if (mdionexus_ofw_fill_ranges(parent, sc) < 0) {
		device_printf(dev, "could not get ranges\n");
		return (ENXIO);
	}
	/* Iterate through all bus subordinates */
	for (node = OF_child(parent); node > 0; node = OF_peer(node)) {
		/* Allocate and populate devinfo. */
		di = malloc(sizeof(*di), M_THUNDER_MDIO, M_WAITOK | M_ZERO);
		if (ofw_bus_gen_setup_devinfo(&di->di_dinfo, node) != 0) {
			free(di, M_THUNDER_MDIO);
			continue;
		}

		/* Initialize and populate resource list. */
		resource_list_init(&di->di_rl);
		ofw_bus_reg_to_rl(dev, node, sc->acells, sc->scells,
		    &di->di_rl);
		ofw_bus_intr_to_rl(dev, node, &di->di_rl, NULL);

		/* Add newbus device for this FDT node */
		child = device_add_child(dev, NULL, -1);
		if (child == NULL) {
			resource_list_free(&di->di_rl);
			ofw_bus_gen_destroy_devinfo(&di->di_dinfo);
			free(di, M_THUNDER_MDIO);
			continue;
		}

		device_set_ivars(child, di);
	}

	return (0);
}