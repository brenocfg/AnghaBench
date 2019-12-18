#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct TYPE_7__ {int shift; int mask; int cond_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  cond_value; int /*<<< orphan*/  cond_shift; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int shift; int mask; int cond_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  cond_value; int /*<<< orphan*/  cond_shift; int /*<<< orphan*/  value; } ;
struct aw_clk_prediv_mux_sc {int mux_shift; int mux_mask; int /*<<< orphan*/  flags; TYPE_3__ prediv; TYPE_1__ div; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {int shift; int width; int cond_width; int cond_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  cond_value; int /*<<< orphan*/  cond_shift; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int shift; int width; int cond_width; int /*<<< orphan*/  flags; int /*<<< orphan*/  cond_value; int /*<<< orphan*/  cond_shift; int /*<<< orphan*/  value; } ;
struct aw_clk_prediv_mux_def {int mux_shift; int mux_width; int /*<<< orphan*/  flags; TYPE_4__ prediv; TYPE_2__ div; int /*<<< orphan*/  offset; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  aw_prediv_mux_clknode_class ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct aw_clk_prediv_mux_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
aw_clk_prediv_mux_register(struct clkdom *clkdom, struct aw_clk_prediv_mux_def *clkdef)
{
	struct clknode *clk;
	struct aw_clk_prediv_mux_sc *sc;

	clk = clknode_create(clkdom, &aw_prediv_mux_clknode_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);

	sc->offset = clkdef->offset;

	sc->mux_shift = clkdef->mux_shift;
	sc->mux_mask = ((1 << clkdef->mux_width) - 1) << sc->mux_shift;

	sc->div.shift = clkdef->div.shift;
	sc->div.mask = ((1 << clkdef->div.width) - 1) << sc->div.shift;
	sc->div.value = clkdef->div.value;
	sc->div.cond_shift = clkdef->div.cond_shift;
	sc->div.cond_mask = ((1 << clkdef->div.cond_width) - 1) << sc->div.shift;
	sc->div.cond_value = clkdef->div.cond_value;
	sc->div.flags = clkdef->div.flags;

	sc->prediv.shift = clkdef->prediv.shift;
	sc->prediv.mask = ((1 << clkdef->prediv.width) - 1) << sc->prediv.shift;
	sc->prediv.value = clkdef->prediv.value;
	sc->prediv.cond_shift = clkdef->prediv.cond_shift;
	if (clkdef->prediv.cond_width != 0)
		sc->prediv.cond_mask = ((1 << clkdef->prediv.cond_width) - 1) << sc->prediv.shift;
	else
		sc->prediv.cond_mask = clkdef->prediv.cond_mask;
	sc->prediv.cond_value = clkdef->prediv.cond_value;
	sc->prediv.flags = clkdef->prediv.flags;

	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);

	return (0);
}