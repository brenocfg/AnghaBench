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
struct clknode_fixed_sc {int /*<<< orphan*/  div; int /*<<< orphan*/  mult; int /*<<< orphan*/  freq; int /*<<< orphan*/  fixed_flags; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct clk_fixed_def {int /*<<< orphan*/  div; int /*<<< orphan*/  mult; int /*<<< orphan*/  freq; int /*<<< orphan*/  fixed_flags; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_fixed_class ; 
 struct clknode_fixed_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
clknode_fixed_register(struct clkdom *clkdom, struct clk_fixed_def *clkdef)
{
	struct clknode *clk;
	struct clknode_fixed_sc *sc;

	clk = clknode_create(clkdom, &clknode_fixed_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->fixed_flags = clkdef->fixed_flags;
	sc->freq = clkdef->freq;
	sc->mult = clkdef->mult;
	sc->div = clkdef->div;

	clknode_register(clkdom, clk);
	return (0);
}