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
typedef  int uint32_t ;
struct tegra124_car_softc {int /*<<< orphan*/  clkdom; int /*<<< orphan*/  dev; } ;
struct clk_fixed_def {scalar_t__ freq; int div; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKDEV_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OSC_CTRL ; 
 int OSC_CTRL_OSC_FREQ_SHIFT ; 
 int OSC_CTRL_PLL_REF_DIV_SHIFT ; 
 int clknode_fixed_register (int /*<<< orphan*/ ,struct clk_fixed_def*) ; 
 struct clk_fixed_def fixed_clk_m ; 
 struct clk_fixed_def fixed_osc_div_clk ; 
 scalar_t__* osc_freqs ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
init_fixeds(struct tegra124_car_softc *sc, struct clk_fixed_def *clks,
    int nclks)
{
	int i, rv;
	uint32_t val;
	int osc_idx;

	CLKDEV_READ_4(sc->dev, OSC_CTRL, &val);
	osc_idx = val >> OSC_CTRL_OSC_FREQ_SHIFT;
	fixed_clk_m.freq = osc_freqs[osc_idx];
	if (fixed_clk_m.freq == 0)
		panic("Undefined input frequency");
	rv = clknode_fixed_register(sc->clkdom, &fixed_clk_m);
	if (rv != 0) panic("clk_fixed_register failed");

	val = (val >> OSC_CTRL_PLL_REF_DIV_SHIFT) & 3;
	fixed_osc_div_clk.div = 1 << val;
	rv = clknode_fixed_register(sc->clkdom, &fixed_osc_div_clk);
	if (rv != 0) panic("clk_fixed_register failed");

	for (i = 0; i < nclks; i++) {
		rv = clknode_fixed_register(sc->clkdom, clks + i);
		if (rv != 0)
			panic("clk_fixed_register failed");
	}
}