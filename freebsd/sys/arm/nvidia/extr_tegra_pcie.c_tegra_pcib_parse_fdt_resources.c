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
struct tegra_pcib_softc {scalar_t__ num_ports; struct tegra_pcib_port** ports; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_cml; int /*<<< orphan*/  clk_pll_e; int /*<<< orphan*/  clk_afi; int /*<<< orphan*/  clk_pex; int /*<<< orphan*/  hwreset_pcie_x; int /*<<< orphan*/  hwreset_afi; int /*<<< orphan*/  hwreset_pex; int /*<<< orphan*/  supply_avdd_pll_erefe; int /*<<< orphan*/  supply_vddio_pex_ctl; int /*<<< orphan*/  supply_hvdd_pex_pll_e; int /*<<< orphan*/  supply_hvdd_pex; int /*<<< orphan*/  supply_avdd_pex_pll; int /*<<< orphan*/  supply_dvddio_pex; int /*<<< orphan*/  supply_avddio_pex; } ;
struct tegra_pcib_port {int dummy; } ;
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct tegra_pcib_port* tegra_pcib_parse_port (struct tegra_pcib_softc*,scalar_t__) ; 

__attribute__((used)) static int
tegra_pcib_parse_fdt_resources(struct tegra_pcib_softc *sc, phandle_t node)
{
	phandle_t child;
	struct tegra_pcib_port *port;
	int rv;

	/* Power supplies. */
	rv = regulator_get_by_ofw_property(sc->dev, 0, "avddio-pex-supply",
	    &sc->supply_avddio_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'avddio-pex' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "dvddio-pex-supply",
	     &sc->supply_dvddio_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'dvddio-pex' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "avdd-pex-pll-supply",
	     &sc->supply_avdd_pex_pll);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'avdd-pex-pll' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "hvdd-pex-supply",
	     &sc->supply_hvdd_pex);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'hvdd-pex' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "hvdd-pex-pll-e-supply",
	     &sc->supply_hvdd_pex_pll_e);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'hvdd-pex-pll-e' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "vddio-pex-ctl-supply",
	    &sc->supply_vddio_pex_ctl);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'vddio-pex-ctl' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "avdd-pll-erefe-supply",
	     &sc->supply_avdd_pll_erefe);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot get 'avdd-pll-erefe' regulator\n");
		return (ENXIO);
	}

	/* Resets. */
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "pex", &sc->hwreset_pex);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pex' reset\n");
		return (ENXIO);
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "afi", &sc->hwreset_afi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'afi' reset\n");
		return (ENXIO);
	}
	rv = hwreset_get_by_ofw_name(sc->dev, 0, "pcie_x", &sc->hwreset_pcie_x);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pcie_x' reset\n");
		return (ENXIO);
	}

	/* Clocks. */
	rv = clk_get_by_ofw_name(sc->dev, 0, "pex", &sc->clk_pex);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pex' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "afi", &sc->clk_afi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'afi' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "pll_e", &sc->clk_pll_e);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pll_e' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "cml", &sc->clk_cml);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'cml' clock\n");
		return (ENXIO);
	}

	/* Ports */
	sc->num_ports = 0;
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		port = tegra_pcib_parse_port(sc, child);
		if (port == NULL) {
			device_printf(sc->dev, "Cannot parse PCIe port node\n");
			return (ENXIO);
		}
		sc->ports[sc->num_ports++] = port;
	}

	return (0);
}