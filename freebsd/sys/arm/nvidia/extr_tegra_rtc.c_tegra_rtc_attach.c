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
struct tegra_rtc_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_h; int /*<<< orphan*/ * clk; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct tegra_rtc_softc*) ; 
 int /*<<< orphan*/  LOCK_INIT (struct tegra_rtc_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RTC_INTR_MASK ; 
 int /*<<< orphan*/  RTC_INTR_STATUS ; 
 int /*<<< orphan*/  RTC_SECONDS_ALARM0 ; 
 int /*<<< orphan*/  RTC_SECONDS_ALARM1 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct tegra_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tegra_rtc_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct tegra_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tegra_rtc_intr ; 

__attribute__((used)) static int
tegra_rtc_attach(device_t dev)
{
	int rv, rid;
	struct tegra_rtc_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

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

	/* OFW resources. */
	rv = clk_get_by_ofw_index(dev, 0, 0, &sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get i2c clock: %d\n", rv);
		goto fail;
	}
	rv = clk_enable(sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable clock: %d\n", rv);
		goto fail;
	}

	/* Init hardware. */
	WR4(sc, RTC_SECONDS_ALARM0, 0);
	WR4(sc, RTC_SECONDS_ALARM1, 0);
	WR4(sc, RTC_INTR_STATUS, 0xFFFFFFFF);
	WR4(sc, RTC_INTR_MASK, 0);

	/* Setup  interrupt */
	rv = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, tegra_rtc_intr, sc, &sc->irq_h);
	if (rv) {
		device_printf(dev, "Cannot setup interrupt.\n");
		goto fail;
	}

	/*
	 * Register as a time of day clock with 1-second resolution.
	 *
	 * XXXX Not yet, we don't have support for multiple RTCs
	 */
	/* clock_register(dev, 1000000); */

	return (bus_generic_attach(dev));

fail:
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (sc->irq_h != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_h);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	LOCK_DESTROY(sc);

	return (rv);
}