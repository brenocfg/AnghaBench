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
struct clknode_div_sc {int i_width; int i_mask; int f_width; int f_mask; int /*<<< orphan*/  div_table; int /*<<< orphan*/  div_flags; int /*<<< orphan*/  f_shift; int /*<<< orphan*/  i_shift; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct clk_div_def {int i_width; int f_width; int /*<<< orphan*/  div_table; int /*<<< orphan*/  div_flags; int /*<<< orphan*/  f_shift; int /*<<< orphan*/  i_shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_div_class ; 
 struct clknode_div_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
clknode_div_register(struct clkdom *clkdom, struct clk_div_def *clkdef)
{
	struct clknode *clk;
	struct clknode_div_sc *sc;

	clk = clknode_create(clkdom, &clknode_div_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->offset = clkdef->offset;
	sc->i_shift = clkdef->i_shift;
	sc->i_width = clkdef->i_width;
	sc->i_mask = (1 << clkdef->i_width) - 1;
	sc->f_shift = clkdef->f_shift;
	sc->f_width = clkdef->f_width;
	sc->f_mask = (1 << clkdef->f_width) - 1;
	sc->div_flags = clkdef->div_flags;
	sc->div_table = clkdef->div_table;

	clknode_register(clkdom, clk);
	return (0);
}