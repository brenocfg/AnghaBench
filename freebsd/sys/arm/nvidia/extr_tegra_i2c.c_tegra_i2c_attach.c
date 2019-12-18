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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct tegra_i2c_softc {int bus_freq; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_h; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  clk; scalar_t__ core_freq; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  LOCK_INIT (struct tegra_i2c_softc*) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tegra_i2c_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_get_freq (int /*<<< orphan*/ ,scalar_t__*) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct tegra_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int tegra_i2c_hw_init (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  tegra_i2c_intr ; 

__attribute__((used)) static int
tegra_i2c_attach(device_t dev)
{
	int rv, rid;
	phandle_t node;
	struct tegra_i2c_softc *sc;
	uint64_t freq;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	LOCK_INIT(sc);

	/* Get the memory resource for the register mapping. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot map registers.\n");
		rv = ENXIO;
		goto fail;
	}

	/* Allocate our IRQ resource. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate interrupt.\n");
		rv = ENXIO;
		goto fail;
	}

	/* FDT resources. */
	rv = clk_get_by_ofw_name(dev, 0, "div-clk", &sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get i2c clock: %d\n", rv);
		goto fail;
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "i2c", &sc->reset);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get i2c reset\n");
		return (ENXIO);
	}
	rv = OF_getencprop(node, "clock-frequency", &sc->bus_freq,
	    sizeof(sc->bus_freq));
	if (rv != sizeof(sc->bus_freq)) {
		sc->bus_freq = 100000;
		goto fail;
	}

	/* Request maximum frequency for I2C block 136MHz (408MHz / 3). */
	rv = clk_set_freq(sc->clk, 136000000, CLK_SET_ROUND_DOWN);
	if (rv != 0) {
		device_printf(dev, "Cannot set clock frequency\n");
		goto fail;
	}
	rv = clk_get_freq(sc->clk, &freq);
	if (rv != 0) {
		device_printf(dev, "Cannot get clock frequency\n");
		goto fail;
	}
	sc->core_freq = (uint32_t)freq;

	rv = clk_enable(sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable clock: %d\n", rv);
		goto fail;
	}

	/* Init hardware. */
	rv = tegra_i2c_hw_init(sc);
	if (rv) {
		device_printf(dev, "tegra_i2c_activate failed\n");
		goto fail;
	}

	/* Setup interrupt. */
	rv = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, tegra_i2c_intr, sc, &sc->irq_h);
	if (rv) {
		device_printf(dev, "Cannot setup interrupt.\n");
		goto fail;
	}

	/* Attach the iicbus. */
	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "Could not allocate iicbus instance.\n");
		rv = ENXIO;
		goto fail;
	}

	/* Probe and attach the iicbus. */
	return (bus_generic_attach(dev));

fail:
	if (sc->irq_h != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_h);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	LOCK_DESTROY(sc);

	return (rv);
}