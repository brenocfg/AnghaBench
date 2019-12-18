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
typedef  int /*<<< orphan*/  uint64_t ;
struct tegra124_cpufreq_softc {struct cpu_speed_point* act_speed_point; int /*<<< orphan*/  supply_vdd_cpu; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_pll_x; int /*<<< orphan*/  clk_cpu_g; int /*<<< orphan*/  clk_pll_p; } ;
struct cpu_speed_point {scalar_t__ uvolt; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_parent_by_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct cpu_speed_point* get_speed_point (struct tegra124_cpufreq_softc*,int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
set_cpu_freq(struct tegra124_cpufreq_softc *sc, uint64_t freq)
{
	struct cpu_speed_point *point;
	int rv;

	point = get_speed_point(sc, freq);

	if (sc->act_speed_point->uvolt < point->uvolt) {
		/* set cpu voltage */
		rv = regulator_set_voltage(sc->supply_vdd_cpu,
		    point->uvolt, point->uvolt);
		DELAY(10000);
		if (rv != 0)
			return (rv);
	}

	/* Switch supermux to PLLP first */
	rv = clk_set_parent_by_clk(sc->clk_cpu_g, sc->clk_pll_p);
	if (rv != 0) {
		device_printf(sc->dev, "Can't set parent to PLLP\n");
		return (rv);
	}

	/* Set PLLX frequency */
	rv = clk_set_freq(sc->clk_pll_x, point->freq, CLK_SET_ROUND_DOWN);
	if (rv != 0) {
		device_printf(sc->dev, "Can't set CPU clock frequency\n");
		return (rv);
	}

	rv = clk_set_parent_by_clk(sc->clk_cpu_g, sc->clk_pll_x);
	if (rv != 0) {
		device_printf(sc->dev, "Can't set parent to PLLX\n");
		return (rv);
	}

	if (sc->act_speed_point->uvolt > point->uvolt) {
		/* set cpu voltage */
		rv = regulator_set_voltage(sc->supply_vdd_cpu,
		    point->uvolt, point->uvolt);
		if (rv != 0)
			return (rv);
	}

	sc->act_speed_point = point;

	return (0);
}