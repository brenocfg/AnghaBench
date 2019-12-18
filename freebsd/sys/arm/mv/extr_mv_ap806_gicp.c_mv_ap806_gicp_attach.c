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
struct mv_ap806_gicp_softc {struct intr_map_data_fdt* parent_map_data; int /*<<< orphan*/  spi_ranges; int /*<<< orphan*/  spi_ranges_cnt; int /*<<< orphan*/ * parent; int /*<<< orphan*/  dev; } ;
struct intr_map_data_fdt {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MAP_DATA_FDT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_getencprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 struct mv_ap806_gicp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_alloc_map_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_find_iparent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_ap806_gicp_attach(device_t dev)
{
	struct mv_ap806_gicp_softc *sc;
	phandle_t node, xref, intr_parent;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Look for our parent */
	if ((intr_parent = ofw_bus_find_iparent(node)) == 0) {
		device_printf(dev,
		     "Cannot find our parent interrupt controller\n");
		return (ENXIO);
	}
	if ((sc->parent = OF_device_from_xref(intr_parent)) == NULL) {
		device_printf(dev,
		     "cannot find parent interrupt controller device\n");
		return (ENXIO);
	}

	sc->spi_ranges_cnt = OF_getencprop_alloc(node, "marvell,spi-ranges",
	    (void **)&sc->spi_ranges);

	xref = OF_xref_from_node(node);
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "Cannot register GICP\n");
		return (ENXIO);
	}
	/* Allocate GIC compatible mapping entry (3 cells) */
	sc->parent_map_data = (struct intr_map_data_fdt *)intr_alloc_map_data(
	    INTR_MAP_DATA_FDT, sizeof(struct intr_map_data_fdt) +
	    + 3 * sizeof(phandle_t), M_WAITOK | M_ZERO);
	OF_device_register_xref(xref, dev);

	return (0);
}