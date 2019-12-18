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
struct rk_clk_fract_sc {int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; } ;
struct rk_clk_fract_def {int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  clkdef; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rk_clk_fract_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  rk_clk_fract_class ; 

int
rk_clk_fract_register(struct clkdom *clkdom, struct rk_clk_fract_def *clkdef)
{
	struct clknode *clk;
	struct rk_clk_fract_sc *sc;

	clk = clknode_create(clkdom, &rk_clk_fract_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->flags = clkdef->flags;
	sc->offset = clkdef->offset;

	clknode_register(clkdom, clk);
	return (0);
}