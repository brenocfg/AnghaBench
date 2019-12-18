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
struct tegra124_cpufreq_softc {int /*<<< orphan*/ * clk_dfll; int /*<<< orphan*/ * clk_pll_p; int /*<<< orphan*/ * clk_pll_x; int /*<<< orphan*/ * clk_cpu_lp; int /*<<< orphan*/ * clk_cpu_g; int /*<<< orphan*/ * supply_vdd_cpu; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpufreq_unregister (int /*<<< orphan*/ ) ; 
 struct tegra124_cpufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra124_cpufreq_detach(device_t dev)
{
	struct tegra124_cpufreq_softc *sc;

	sc = device_get_softc(dev);
	cpufreq_unregister(dev);

	if (sc->supply_vdd_cpu != NULL)
		regulator_release(sc->supply_vdd_cpu);

	if (sc->clk_cpu_g != NULL)
		clk_release(sc->clk_cpu_g);
	if (sc->clk_cpu_lp != NULL)
		clk_release(sc->clk_cpu_lp);
	if (sc->clk_pll_x != NULL)
		clk_release(sc->clk_pll_x);
	if (sc->clk_pll_p != NULL)
		clk_release(sc->clk_pll_p);
	if (sc->clk_dfll != NULL)
		clk_release(sc->clk_dfll);
	return (0);
}