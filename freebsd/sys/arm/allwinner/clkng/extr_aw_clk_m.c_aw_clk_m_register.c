#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct TYPE_3__ {int shift; int width; int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct aw_clk_m_sc {int mux_shift; int mux_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  gate_shift; TYPE_1__ m; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct aw_clk_m_def {int mux_shift; int mux_width; int /*<<< orphan*/  flags; int /*<<< orphan*/  gate_shift; TYPE_2__ m; int /*<<< orphan*/  offset; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  aw_m_clknode_class ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct aw_clk_m_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
aw_clk_m_register(struct clkdom *clkdom, struct aw_clk_m_def *clkdef)
{
	struct clknode *clk;
	struct aw_clk_m_sc *sc;

	clk = clknode_create(clkdom, &aw_m_clknode_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);

	sc->offset = clkdef->offset;

	sc->m.shift = clkdef->m.shift;
	sc->m.width = clkdef->m.width;
	sc->m.mask = ((1 << sc->m.width) - 1) << sc->m.shift;
	sc->m.value = clkdef->m.value;
	sc->m.flags = clkdef->m.flags;

	sc->mux_shift = clkdef->mux_shift;
	sc->mux_mask = ((1 << clkdef->mux_width) - 1) << sc->mux_shift;

	sc->gate_shift = clkdef->gate_shift;

	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);

	return (0);
}