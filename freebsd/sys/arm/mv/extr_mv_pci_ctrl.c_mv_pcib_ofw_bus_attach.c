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
struct mv_pcib_ctrl_softc {int addr_cells; int size_cells; } ;
struct TYPE_5__ {int /*<<< orphan*/  obd_name; } ;
struct mv_pcib_ctrl_devinfo {int /*<<< orphan*/  di_rl; TYPE_2__ di_dinfo; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  (* get_rl_t ) (int /*<<< orphan*/ *,scalar_t__,int,int,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_PCIB_CTRL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct mv_pcib_ctrl_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct mv_pcib_ctrl_devinfo*) ; 
 int /*<<< orphan*/  free (struct mv_pcib_ctrl_devinfo*,int /*<<< orphan*/ ) ; 
 struct mv_pcib_ctrl_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv_pcib_ctrl_compat ; 
 scalar_t__ mv_pcib_ctrl_fill_ranges (scalar_t__,struct mv_pcib_ctrl_softc*) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_2__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mv_pcib_ofw_bus_attach(device_t dev)
{
	struct mv_pcib_ctrl_devinfo *di;
	struct mv_pcib_ctrl_softc *sc;
	device_t child;
	phandle_t parent, node;
	get_rl_t get_rl;

	parent = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);
	if (parent > 0) {
		sc->addr_cells = 1;
		if (OF_getencprop(parent, "#address-cells", &(sc->addr_cells),
		    sizeof(sc->addr_cells)) <= 0)
			return(ENXIO);

		sc->size_cells = 1;
		if (OF_getencprop(parent, "#size-cells", &(sc->size_cells),
		    sizeof(sc->size_cells)) <= 0)
			return(ENXIO);

		for (node = OF_child(parent); node > 0; node = OF_peer(node)) {
			di = malloc(sizeof(*di), M_PCIB_CTRL, M_WAITOK | M_ZERO);
			if (ofw_bus_gen_setup_devinfo(&di->di_dinfo, node)) {
				if (bootverbose) {
					device_printf(dev,
					    "Could not set up devinfo for PCI\n");
				}
				free(di, M_PCIB_CTRL);
				continue;
			}

			child = device_add_child(dev, NULL, -1);
			if (child == NULL) {
				if (bootverbose) {
					device_printf(dev,
					    "Could not add child: %s\n",
					    di->di_dinfo.obd_name);
				}
				ofw_bus_gen_destroy_devinfo(&di->di_dinfo);
				free(di, M_PCIB_CTRL);
				continue;
			}

			resource_list_init(&di->di_rl);
			get_rl = (get_rl_t) ofw_bus_search_compatible(dev,
			    mv_pcib_ctrl_compat)->ocd_data;
			if (get_rl != NULL)
				get_rl(child, node, sc->addr_cells,
				    sc->size_cells, &di->di_rl);

			device_set_ivars(child, di);
		}
	}

	if (mv_pcib_ctrl_fill_ranges(parent, sc) < 0) {
		device_printf(dev, "could not get ranges\n");
		return (ENXIO);
	}

	return (0);
}