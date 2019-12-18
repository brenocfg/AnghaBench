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
struct aw_dwc3_softc {int /*<<< orphan*/  sc; int /*<<< orphan*/  rst_bus; int /*<<< orphan*/  clk_bus; int /*<<< orphan*/ * dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 struct aw_dwc3_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_name (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simplebus_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ simplebus_fill_ranges (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
aw_dwc3_attach(device_t dev)
{
	struct aw_dwc3_softc *sc;
	device_t cdev;
	phandle_t node, child;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Enable the clocks */
	if (clk_get_by_ofw_name(dev, 0, "bus", &sc->clk_bus) != 0) {
		device_printf(dev, "Cannot get bus clock\n");
		return (ENXIO);
	}
	err = clk_enable(sc->clk_bus);
	if (err != 0) {
		device_printf(dev, "Could not enable clock %s\n",
		    clk_get_name(sc->clk_bus));
		return (ENXIO);
	}

	/* Put module out of reset */
	if (hwreset_get_by_ofw_name(dev, node, "bus", &sc->rst_bus) == 0) {
		if (hwreset_deassert(sc->rst_bus) != 0) {
			device_printf(dev, "Cannot deassert reset\n");
			return (ENXIO);
		}
	}

	simplebus_init(dev, node);
	if (simplebus_fill_ranges(node, &sc->sc) < 0) {
		device_printf(dev, "could not get ranges\n");
		return (ENXIO);
	}

	for (child = OF_child(node); child > 0; child = OF_peer(child)) {
		cdev = simplebus_add_device(dev, child, 0, NULL, -1, NULL);
		if (cdev != NULL)
			device_probe_and_attach(cdev);
	}

	return (bus_generic_attach(dev));
}