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
struct rk_clk_pll_sc {int /*<<< orphan*/  frac_rates; int /*<<< orphan*/  rates; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode_shift; int /*<<< orphan*/  mode_reg; int /*<<< orphan*/  gate_shift; int /*<<< orphan*/  gate_offset; int /*<<< orphan*/  base_offset; } ;
struct rk_clk_pll_def {int /*<<< orphan*/  frac_rates; int /*<<< orphan*/  rates; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode_shift; int /*<<< orphan*/  mode_reg; int /*<<< orphan*/  gate_shift; int /*<<< orphan*/  gate_offset; int /*<<< orphan*/  base_offset; int /*<<< orphan*/  clkdef; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rk_clk_pll_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  rk3328_clk_pll_clknode_class ; 

int
rk3328_clk_pll_register(struct clkdom *clkdom, struct rk_clk_pll_def *clkdef)
{
	struct clknode *clk;
	struct rk_clk_pll_sc *sc;

	clk = clknode_create(clkdom, &rk3328_clk_pll_clknode_class,
	    &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);

	sc->base_offset = clkdef->base_offset;
	sc->gate_offset = clkdef->gate_offset;
	sc->gate_shift = clkdef->gate_shift;
	sc->mode_reg = clkdef->mode_reg;
	sc->mode_shift = clkdef->mode_shift;
	sc->flags = clkdef->flags;
	sc->rates = clkdef->rates;
	sc->frac_rates = clkdef->frac_rates;

	clknode_register(clkdom, clk);

	return (0);
}