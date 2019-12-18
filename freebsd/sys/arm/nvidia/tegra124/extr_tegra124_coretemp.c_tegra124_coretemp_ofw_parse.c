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
struct tegra124_coretemp_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * tsens_dev; scalar_t__ cpu_id; scalar_t__ tsens_id; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * OF_device_from_xref (scalar_t__) ; 
 scalar_t__ OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 int ofw_bus_parse_xref_list_alloc (scalar_t__,char*,char*,int /*<<< orphan*/ ,scalar_t__*,int*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
tegra124_coretemp_ofw_parse(struct tegra124_coretemp_softc *sc)
{
	int rv, ncells;
	phandle_t node, xnode;
	pcell_t *cells;

	node = OF_peer(0);
	node = ofw_bus_find_child(node, "thermal-zones");
	if (node <= 0) {
		device_printf(sc->dev, "Cannot find 'thermal-zones'.\n");
		return (ENXIO);
	}

	node = ofw_bus_find_child(node, "cpu");
	if (node <= 0) {
		device_printf(sc->dev, "Cannot find 'cpu'\n");
		return (ENXIO);
	}
	rv = ofw_bus_parse_xref_list_alloc(node, "thermal-sensors",
	    "#thermal-sensor-cells", 0, &xnode, &ncells, &cells);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot parse 'thermal-sensors' property.\n");
		return (ENXIO);
	}
	if (ncells != 1) {
		device_printf(sc->dev,
		    "Invalid format of 'thermal-sensors' property(%d).\n",
		    ncells);
		return (ENXIO);
	}

	sc->tsens_id = 0x100 + sc->cpu_id; //cells[0];
	OF_prop_free(cells);

	sc->tsens_dev = OF_device_from_xref(xnode);
	if (sc->tsens_dev == NULL) {
		device_printf(sc->dev,
		    "Cannot find thermal sensors device.");
		return (ENXIO);
	}
	return (0);
}