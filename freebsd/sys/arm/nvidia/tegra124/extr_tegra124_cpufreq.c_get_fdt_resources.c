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
struct tegra124_cpufreq_softc {int /*<<< orphan*/  clk_dfll; int /*<<< orphan*/  clk_pll_p; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_pll_x; int /*<<< orphan*/  clk_cpu_lp; int /*<<< orphan*/  clk_cpu_g; int /*<<< orphan*/  supply_vdd_cpu; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_fdt_resources(struct tegra124_cpufreq_softc *sc, phandle_t node)
{
	int rv;
	device_t parent_dev;

	parent_dev =  device_get_parent(sc->dev);
	rv = regulator_get_by_ofw_property(parent_dev, 0, "vdd-cpu-supply",
	    &sc->supply_vdd_cpu);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'vdd-cpu' regulator\n");
		return (rv);
	}

	rv = clk_get_by_ofw_name(parent_dev, 0, "cpu_g", &sc->clk_cpu_g);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'cpu_g' clock: %d\n", rv);
		return (ENXIO);
	}

	rv = clk_get_by_ofw_name(parent_dev, 0, "cpu_lp", &sc->clk_cpu_lp);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'cpu_lp' clock\n");
		return (ENXIO);
	}

	rv = clk_get_by_ofw_name(parent_dev, 0, "pll_x", &sc->clk_pll_x);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pll_x' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(parent_dev, 0, "pll_p", &sc->clk_pll_p);
	if (rv != 0) {
		device_printf(parent_dev, "Cannot get 'pll_p' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(parent_dev, 0, "dfll", &sc->clk_dfll);
	if (rv != 0) {
		/* XXX DPLL is not implemented yet */
/*
		device_printf(sc->dev, "Cannot get 'dfll' clock\n");
		return (ENXIO);
*/
	}
	return (0);
}