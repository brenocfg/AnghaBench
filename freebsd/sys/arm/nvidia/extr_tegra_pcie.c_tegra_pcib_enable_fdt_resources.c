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
struct tegra_pcib_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_pll_e; int /*<<< orphan*/  clk_cml; int /*<<< orphan*/  clk_afi; int /*<<< orphan*/  hwreset_afi; int /*<<< orphan*/  hwreset_pex; int /*<<< orphan*/  clk_pex; int /*<<< orphan*/  supply_avdd_pll_erefe; int /*<<< orphan*/  supply_vddio_pex_ctl; int /*<<< orphan*/  supply_hvdd_pex_pll_e; int /*<<< orphan*/  supply_hvdd_pex; int /*<<< orphan*/  supply_avdd_pex_pll; int /*<<< orphan*/  supply_dvddio_pex; int /*<<< orphan*/  supply_avddio_pex; int /*<<< orphan*/  hwreset_pcie_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_PCX ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_assert (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int tegra_powergate_sequence_power_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_pcib_enable_fdt_resources(struct tegra_pcib_softc *sc)
{
	int rv;

	rv = hwreset_assert(sc->hwreset_pcie_x);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert 'pcie_x' reset\n");
		return (rv);
	}
	rv = hwreset_assert(sc->hwreset_afi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert  'afi' reset\n");
		return (rv);
	}
	rv = hwreset_assert(sc->hwreset_pex);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert  'pex' reset\n");
		return (rv);
	}

	tegra_powergate_power_off(TEGRA_POWERGATE_PCX);

	/* Power supplies. */
	rv = regulator_enable(sc->supply_avddio_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'avddio_pex' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_dvddio_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'dvddio_pex' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_avdd_pex_pll);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'avdd-pex-pll' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_hvdd_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'hvdd-pex-supply' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_hvdd_pex_pll_e);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'hvdd-pex-pll-e-supply' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_vddio_pex_ctl);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'vddio-pex-ctl' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_avdd_pll_erefe);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot enable 'avdd-pll-erefe-supply' regulator\n");
		return (rv);
	}

	rv = tegra_powergate_sequence_power_up(TEGRA_POWERGATE_PCX,
	    sc->clk_pex, sc->hwreset_pex);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'PCX' powergate\n");
		return (rv);
	}

	rv = hwreset_deassert(sc->hwreset_afi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot unreset 'afi' reset\n");
		return (rv);
	}

	rv = clk_enable(sc->clk_afi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'afi' clock\n");
		return (rv);
	}
	rv = clk_enable(sc->clk_cml);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'cml' clock\n");
		return (rv);
	}
	rv = clk_enable(sc->clk_pll_e);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'pll_e' clock\n");
		return (rv);
	}
	return (0);
}