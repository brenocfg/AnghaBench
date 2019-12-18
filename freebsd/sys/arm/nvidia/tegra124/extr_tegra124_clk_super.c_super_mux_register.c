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
struct super_mux_sc {int /*<<< orphan*/  flags; int /*<<< orphan*/  src_div2; int /*<<< orphan*/  src_pllx; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  clkdev; } ;
struct super_mux_def {int /*<<< orphan*/  flags; int /*<<< orphan*/  src_div2; int /*<<< orphan*/  src_pllx; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  clkdef; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_get_device (struct clknode*) ; 
 struct super_mux_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  tegra124_super_mux_class ; 

__attribute__((used)) static int
super_mux_register(struct clkdom *clkdom, struct super_mux_def *clkdef)
{
	struct clknode *clk;
	struct super_mux_sc *sc;

	clk = clknode_create(clkdom, &tegra124_super_mux_class,
	    &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->clkdev = clknode_get_device(clk);
	sc->base_reg = clkdef->base_reg;
	sc->src_pllx = clkdef->src_pllx;
	sc->src_div2 = clkdef->src_div2;
	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);
	return (0);
}