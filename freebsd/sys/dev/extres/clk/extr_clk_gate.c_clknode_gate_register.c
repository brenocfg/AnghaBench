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
struct clknode_gate_sc {int /*<<< orphan*/  gate_flags; int /*<<< orphan*/  off_value; int /*<<< orphan*/  on_value; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct clk_gate_def {int /*<<< orphan*/  gate_flags; int /*<<< orphan*/  off_value; int /*<<< orphan*/  on_value; int /*<<< orphan*/  mask; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_gate_class ; 
 struct clknode_gate_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
clknode_gate_register(struct clkdom *clkdom, struct clk_gate_def *clkdef)
{
	struct clknode *clk;
	struct clknode_gate_sc *sc;

	clk = clknode_create(clkdom, &clknode_gate_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->offset = clkdef->offset;
	sc->shift = clkdef->shift;
	sc->mask =  clkdef->mask;
	sc->on_value = clkdef->on_value;
	sc->off_value = clkdef->off_value;
	sc->gate_flags = clkdef->gate_flags;

	clknode_register(clkdom, clk);
	return (0);
}