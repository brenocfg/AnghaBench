#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ti_clk_mux {int flags; int num_parents; int /*<<< orphan*/  reg; int /*<<< orphan*/  module; int /*<<< orphan*/  bit_shift; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  index; } ;
struct clk_omap_mux {int mask; struct clk_hw hw; int /*<<< orphan*/  flags; TYPE_1__ reg; int /*<<< orphan*/  latch; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int CLKF_INDEX_STARTS_AT_ONE ; 
 int /*<<< orphan*/  CLK_MUX_INDEX_ONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fls (int) ; 
 struct clk_omap_mux* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *ti_clk_build_component_mux(struct ti_clk_mux *setup)
{
	struct clk_omap_mux *mux;
	int num_parents;

	if (!setup)
		return NULL;

	mux = kzalloc(sizeof(*mux), GFP_KERNEL);
	if (!mux)
		return ERR_PTR(-ENOMEM);

	mux->shift = setup->bit_shift;
	mux->latch = -EINVAL;

	mux->reg.index = setup->module;
	mux->reg.offset = setup->reg;

	if (setup->flags & CLKF_INDEX_STARTS_AT_ONE)
		mux->flags |= CLK_MUX_INDEX_ONE;

	num_parents = setup->num_parents;

	mux->mask = num_parents - 1;
	mux->mask = (1 << fls(mux->mask)) - 1;

	return &mux->hw;
}