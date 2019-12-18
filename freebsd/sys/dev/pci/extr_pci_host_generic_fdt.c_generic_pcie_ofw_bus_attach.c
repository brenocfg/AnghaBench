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
struct generic_pcie_ofw_devinfo {int /*<<< orphan*/  di_dinfo; int /*<<< orphan*/  di_rl; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct generic_pcie_ofw_devinfo*) ; 
 int /*<<< orphan*/  free (struct generic_pcie_ofw_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_addr_size_cells (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct generic_pcie_ofw_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_intr_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_reg_to_rl (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
generic_pcie_ofw_bus_attach(device_t dev)
{
	struct generic_pcie_ofw_devinfo *di;
	device_t child;
	phandle_t parent, node;
	pcell_t addr_cells, size_cells;

	parent = ofw_bus_get_node(dev);
	if (parent > 0) {
		get_addr_size_cells(parent, &addr_cells, &size_cells);
		/* Iterate through all bus subordinates */
		for (node = OF_child(parent); node > 0; node = OF_peer(node)) {

			/* Allocate and populate devinfo. */
			di = malloc(sizeof(*di), M_DEVBUF, M_WAITOK | M_ZERO);
			if (ofw_bus_gen_setup_devinfo(&di->di_dinfo, node) != 0) {
				free(di, M_DEVBUF);
				continue;
			}

			/* Initialize and populate resource list. */
			resource_list_init(&di->di_rl);
			ofw_bus_reg_to_rl(dev, node, addr_cells, size_cells,
			    &di->di_rl);
			ofw_bus_intr_to_rl(dev, node, &di->di_rl, NULL);

			/* Add newbus device for this FDT node */
			child = device_add_child(dev, NULL, -1);
			if (child == NULL) {
				resource_list_free(&di->di_rl);
				ofw_bus_gen_destroy_devinfo(&di->di_dinfo);
				free(di, M_DEVBUF);
				continue;
			}

			device_set_ivars(child, di);
		}
	}

	return (0);
}