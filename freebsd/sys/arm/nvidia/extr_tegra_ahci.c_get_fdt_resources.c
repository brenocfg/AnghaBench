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
struct tegra_ahci_sc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_pll_e; int /*<<< orphan*/  clk_cml; int /*<<< orphan*/  clk_sata_oob; int /*<<< orphan*/  clk_sata; int /*<<< orphan*/  phy; int /*<<< orphan*/  hwreset_sata_cold; int /*<<< orphan*/  hwreset_sata_oob; int /*<<< orphan*/  hwreset_sata; int /*<<< orphan*/  supply_target_12v; int /*<<< orphan*/  supply_target_5v; int /*<<< orphan*/  supply_avdd; int /*<<< orphan*/  supply_vddio; int /*<<< orphan*/  supply_hvdd; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int phy_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_fdt_resources(struct tegra_ahci_sc *sc, phandle_t node)
{
	int rv;


	rv = regulator_get_by_ofw_property(sc->dev, 0, "hvdd-supply",
	    &sc->supply_hvdd );
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'hvdd' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "vddio-supply",
	    &sc->supply_vddio);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'vddio' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "avdd-supply",
	    &sc->supply_avdd);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'avdd' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "target-5v-supply",
	    &sc->supply_target_5v);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'target-5v' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "target-12v-supply",
	    &sc->supply_target_12v);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'target-12v' regulator\n");
		return (ENXIO);
	}

	rv = hwreset_get_by_ofw_name(sc->dev, 0, "sata", &sc->hwreset_sata );
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata' reset\n");
		return (ENXIO);
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "sata-oob",
	    &sc->hwreset_sata_oob);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata oob' reset\n");
		return (ENXIO);
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "sata-cold",
	    &sc->hwreset_sata_cold);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata cold' reset\n");
		return (ENXIO);
	}

	rv = phy_get_by_ofw_name(sc->dev, 0, "sata-0", &sc->phy);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata' phy\n");
		return (ENXIO);
	}

	rv = clk_get_by_ofw_name(sc->dev, 0, "sata", &sc->clk_sata);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "sata-oob", &sc->clk_sata_oob);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'sata oob' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "cml1", &sc->clk_cml);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'cml1' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "pll_e", &sc->clk_pll_e);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pll_e' clock\n");
		return (ENXIO);
	}
	return (0);
}