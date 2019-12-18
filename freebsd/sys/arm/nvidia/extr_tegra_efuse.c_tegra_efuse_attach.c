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
struct tegra_efuse_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * clk; int /*<<< orphan*/  fuse_begin; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TEGRA124_FUSE_BEGIN ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct tegra_efuse_softc* dev_sc ; 
 struct tegra_efuse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hwreset_deassert (int /*<<< orphan*/ *) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra124_init_speedo (struct tegra_efuse_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_efuse_dump_sku () ; 
 int /*<<< orphan*/  tegra_sku_info ; 

__attribute__((used)) static int
tegra_efuse_attach(device_t dev)
{
	int rv, rid;
	phandle_t node;
	struct tegra_efuse_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Get the memory resource for the register mapping. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot map registers.\n");
		rv = ENXIO;
		goto fail;
	}

	/* OFW resources. */
	rv = clk_get_by_ofw_name(dev, 0, "fuse", &sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get fuse clock: %d\n", rv);
		goto fail;
	}
	rv = clk_enable(sc->clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable clock: %d\n", rv);
		goto fail;
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "fuse", &sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot get fuse reset\n");
		goto fail;
	}
	rv = hwreset_deassert(sc->reset);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot clear reset\n");
		goto fail;
	}

	/* Tegra124 specific init. */
	sc->fuse_begin = TEGRA124_FUSE_BEGIN;
	tegra124_init_speedo(sc, &tegra_sku_info);

	dev_sc = sc;

	if (bootverbose)
		tegra_efuse_dump_sku();
	return (bus_generic_attach(dev));

fail:
	dev_sc = NULL;
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (sc->reset != NULL)
		hwreset_release(sc->reset);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);

	return (rv);
}