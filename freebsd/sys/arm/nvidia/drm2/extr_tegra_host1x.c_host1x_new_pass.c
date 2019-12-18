#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct host1x_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct host1x_softc {int attach_done; TYPE_1__ irq_hook; int /*<<< orphan*/  syncpt_irq_h; int /*<<< orphan*/ * syncpt_irq_res; int /*<<< orphan*/  gen_irq_h; int /*<<< orphan*/ * gen_irq_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset; int /*<<< orphan*/  clk; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_PASS_DEFAULT ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_current_pass ; 
 int /*<<< orphan*/  bus_generic_new_pass (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct host1x_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_detach (int /*<<< orphan*/ ) ; 
 struct host1x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  host1x_gen_intr ; 
 int /*<<< orphan*/  host1x_irq_hook ; 
 int /*<<< orphan*/  host1x_syncpt_intr ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
host1x_new_pass(device_t dev)
{
	struct host1x_softc *sc;
	int rv, rid;
	phandle_t node;

	/*
	 * We attach during BUS_PASS_BUS (because we must overcome simplebus),
	 * but some of our FDT resources are not ready until BUS_PASS_DEFAULT
	 */
	sc = device_get_softc(dev);
	if (sc->attach_done || bus_current_pass < BUS_PASS_DEFAULT) {
		bus_generic_new_pass(dev);
		return;
	}

	sc->attach_done = 1;
	node = ofw_bus_get_node(dev);

	/* Allocate our IRQ resource. */
	rid = 0;
	sc->syncpt_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->syncpt_irq_res == NULL) {
		device_printf(dev, "Cannot allocate interrupt.\n");
		rv = ENXIO;
		goto fail;
	}
	rid = 1;
	sc->gen_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->gen_irq_res == NULL) {
		device_printf(dev, "Cannot allocate interrupt.\n");
		rv = ENXIO;
		goto fail;
	}

	/* FDT resources */
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "host1x", &sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot get fuse reset\n");
		goto fail;
	}
	rv = clk_get_by_ofw_index(sc->dev, 0, 0, &sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get i2c clock: %d\n", rv);
		goto fail;
	}

	rv = clk_enable(sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable clock: %d\n", rv);
		goto fail;
	}
	rv = hwreset_deassert(sc->reset);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot clear reset\n");
		goto fail;
	}

	/* Setup  interrupts */
	rv = bus_setup_intr(dev, sc->gen_irq_res,
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, host1x_gen_intr,
	    sc, &sc->gen_irq_h);
	if (rv) {
		device_printf(dev, "Cannot setup gen interrupt.\n");
		goto fail;
	}

	rv = bus_setup_intr(dev, sc->syncpt_irq_res,
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, host1x_syncpt_intr,
	    sc, &sc->syncpt_irq_h);
	if (rv) {
		device_printf(dev, "Cannot setup syncpt interrupt.\n");
		goto fail;
	}

	simplebus_init(dev, 0);
	for (node = OF_child(node); node > 0; node = OF_peer(node))
	    simplebus_add_device(dev, node, 0, NULL, -1, NULL);

	sc->irq_hook.ich_func = host1x_irq_hook;
	sc->irq_hook.ich_arg = sc;
	config_intrhook_establish(&sc->irq_hook);
	bus_generic_new_pass(dev);
	return;

fail:
	device_detach(dev);
	return;
}