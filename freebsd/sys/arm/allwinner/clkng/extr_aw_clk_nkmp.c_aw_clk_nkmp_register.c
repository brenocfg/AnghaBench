#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct TYPE_15__ {int shift; int width; int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_13__ {int shift; int width; int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int shift; int width; int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_9__ {int shift; int width; int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct aw_clk_nkmp_sc {int mux_shift; int mux_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  update_shift; int /*<<< orphan*/  lock_retries; int /*<<< orphan*/  lock_shift; int /*<<< orphan*/  gate_shift; TYPE_7__ p; TYPE_5__ m; TYPE_3__ k; TYPE_1__ n; int /*<<< orphan*/  offset; } ;
struct TYPE_16__ {int shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_14__ {int shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_12__ {int shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  value; } ;
struct aw_clk_nkmp_def {int mux_shift; int mux_width; int /*<<< orphan*/  flags; int /*<<< orphan*/  update_shift; int /*<<< orphan*/  lock_retries; int /*<<< orphan*/  lock_shift; int /*<<< orphan*/  gate_shift; TYPE_8__ p; TYPE_6__ m; TYPE_4__ k; TYPE_2__ n; int /*<<< orphan*/  offset; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  aw_nkmp_clknode_class ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct aw_clk_nkmp_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 

int
aw_clk_nkmp_register(struct clkdom *clkdom, struct aw_clk_nkmp_def *clkdef)
{
	struct clknode *clk;
	struct aw_clk_nkmp_sc *sc;

	clk = clknode_create(clkdom, &aw_nkmp_clknode_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);

	sc->offset = clkdef->offset;

	sc->n.shift = clkdef->n.shift;
	sc->n.width = clkdef->n.width;
	sc->n.mask = ((1 << clkdef->n.width) - 1) << sc->n.shift;
	sc->n.value = clkdef->n.value;
	sc->n.flags = clkdef->n.flags;

	sc->k.shift = clkdef->k.shift;
	sc->k.width = clkdef->k.width;
	sc->k.mask = ((1 << clkdef->k.width) - 1) << sc->k.shift;
	sc->k.value = clkdef->k.value;
	sc->k.flags = clkdef->k.flags;

	sc->m.shift = clkdef->m.shift;
	sc->m.width = clkdef->m.width;
	sc->m.mask = ((1 << clkdef->m.width) - 1) << sc->m.shift;
	sc->m.value = clkdef->m.value;
	sc->m.flags = clkdef->m.flags;

	sc->p.shift = clkdef->p.shift;
	sc->p.width = clkdef->p.width;
	sc->p.mask = ((1 << clkdef->p.width) - 1) << sc->p.shift;
	sc->p.value = clkdef->p.value;
	sc->p.flags = clkdef->p.flags;

	sc->mux_shift = clkdef->mux_shift;
	sc->mux_mask = ((1 << clkdef->mux_width) - 1) << sc->mux_shift;

	sc->gate_shift = clkdef->gate_shift;
	sc->lock_shift = clkdef->lock_shift;
	sc->lock_retries = clkdef->lock_retries;
	sc->update_shift = clkdef->update_shift;
	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);

	return (0);
}