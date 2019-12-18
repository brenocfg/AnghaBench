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
struct periph_sc {int div_width; int div_mask; int div_f_width; int div_f_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  clkdev; } ;
struct periph_def {int div_width; int div_f_width; int /*<<< orphan*/  flags; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  clkdef; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_get_device (struct clknode*) ; 
 struct periph_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  tegra124_periph_class ; 

__attribute__((used)) static int
periph_register(struct clkdom *clkdom, struct periph_def *clkdef)
{
	struct clknode *clk;
	struct periph_sc *sc;

	clk = clknode_create(clkdom, &tegra124_periph_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->clkdev = clknode_get_device(clk);
	sc->base_reg = clkdef->base_reg;
	sc->div_width = clkdef->div_width;
	sc->div_mask = (1 <<clkdef->div_width) - 1;
	sc->div_f_width = clkdef->div_f_width;
	sc->div_f_mask = (1 <<clkdef->div_f_width) - 1;
	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);
	return (0);
}