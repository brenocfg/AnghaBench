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
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ uint32_t ;
struct jz4780_nemc_softc {scalar_t__ clock_tick_psecs; int /*<<< orphan*/  clk; int /*<<< orphan*/  simplebus_sc; int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_freq (int /*<<< orphan*/ ,unsigned long long*) ; 
 struct jz4780_nemc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jz4780_nemc_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ jz4780_nemc_fill_ranges (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_nemc_spec ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
jz4780_nemc_attach(device_t dev)
{
	struct jz4780_nemc_softc *sc = device_get_softc(dev);
	phandle_t node;
	uint64_t freq;

	sc->dev = dev;

	if (bus_alloc_resources(dev, jz4780_nemc_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);

	/* Initialize simplebus and enumerate resources */
	simplebus_init(dev, node);

	if (jz4780_nemc_fill_ranges(node, &sc->simplebus_sc) < 0)
		goto error;

	/* Figure our underlying clock rate. */
	if (clk_get_by_ofw_index(dev, 0, 0, &sc->clk) != 0) {
		device_printf(dev, "could not lookup device clock\n");
		goto error;
	}
	if (clk_enable(sc->clk) != 0) {
		device_printf(dev, "could not enable device clock\n");
		goto error;
	}
	if (clk_get_freq(sc->clk, &freq) != 0) {
		device_printf(dev, "could not determine clock speed\n");
		goto error;
	}

	/* Convert clock frequency to picoseconds-per-tick value. */
	sc->clock_tick_psecs = (uint32_t)(1000000000000ULL / freq);

	/*
	 * Allow devices to identify.
	 */
	bus_generic_probe(dev);

	/*
	 * Now walk the tree and attach top level devices
	 */
	for (node = OF_child(node); node > 0; node = OF_peer(node))
		simplebus_add_device(dev, node, 0, NULL, -1, NULL);

	return (bus_generic_attach(dev));
error:
	jz4780_nemc_detach(dev);
	return (ENXIO);
}