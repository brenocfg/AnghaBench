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
struct tegra_ahci_sc {int /*<<< orphan*/  dev; int /*<<< orphan*/  phy; int /*<<< orphan*/  hwreset_sata_oob; int /*<<< orphan*/  hwreset_sata_cold; int /*<<< orphan*/  clk_pll_e; int /*<<< orphan*/  clk_cml; int /*<<< orphan*/  clk_sata_oob; int /*<<< orphan*/  hwreset_sata; int /*<<< orphan*/  clk_sata; int /*<<< orphan*/  supply_target_12v; int /*<<< orphan*/  supply_target_5v; int /*<<< orphan*/  supply_avdd; int /*<<< orphan*/  supply_vddio; int /*<<< orphan*/  supply_hvdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_SAX ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_assert (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int phy_enable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_fdt_resources(struct tegra_ahci_sc *sc)
{
	int rv;

	rv = regulator_enable(sc->supply_hvdd);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'hvdd' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_vddio);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'vddio' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_avdd);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'avdd' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_target_5v);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable  'target-5v' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_target_12v);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable  'sc->target-12v' regulator\n");
		return (rv);
	}

	/* Stop clocks */
	clk_stop(sc->clk_sata);
	clk_stop(sc->clk_sata_oob);
	tegra_powergate_power_off(TEGRA_POWERGATE_SAX);

	rv = hwreset_assert(sc->hwreset_sata);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert 'sata' reset\n");
		return (rv);
	}
	rv = hwreset_assert(sc->hwreset_sata_oob);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert 'sata oob' reset\n");
		return (rv);
	}

	rv = hwreset_assert(sc->hwreset_sata_cold);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert 'sata cold' reset\n");
		return (rv);
	}
	rv = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_SAX,
	    sc->clk_sata, sc->hwreset_sata);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'SAX' powergate\n");
		return (rv);
	}

	rv = clk_enable(sc->clk_sata_oob);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'sata oob' clock\n");
		return (rv);
	}
	rv = clk_enable(sc->clk_cml);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'cml' clock\n");
		return (rv);
	}
	rv = clk_enable(sc->clk_pll_e);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'pll e' clock\n");
		return (rv);
	}

	rv = hwreset_deassert(sc->hwreset_sata_cold);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot unreset 'sata cold' reset\n");
		return (rv);
	}
	rv = hwreset_deassert(sc->hwreset_sata_oob);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot unreset 'sata oob' reset\n");
		return (rv);
	}

	rv = phy_enable(sc->phy);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable SATA phy\n");
		return (rv);
	}

	return (0);
}