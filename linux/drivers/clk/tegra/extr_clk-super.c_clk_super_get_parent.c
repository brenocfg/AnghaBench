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
typedef  int u8 ;
typedef  int u32 ;
struct tegra_clk_super_mux {int flags; int pllx_index; int div2_index; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SUPER_LP_DIV2_BYPASS ; 
 int /*<<< orphan*/  SUPER_STATE_IDLE ; 
 int SUPER_STATE_MASK ; 
 int /*<<< orphan*/  SUPER_STATE_RUN ; 
 int TEGRA_DIVIDER_2 ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int super_state (int /*<<< orphan*/ ) ; 
 int super_state_to_src_mask (struct tegra_clk_super_mux*) ; 
 int super_state_to_src_shift (struct tegra_clk_super_mux*,int /*<<< orphan*/ ) ; 
 struct tegra_clk_super_mux* to_clk_super_mux (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_super_get_parent(struct clk_hw *hw)
{
	struct tegra_clk_super_mux *mux = to_clk_super_mux(hw);
	u32 val, state;
	u8 source, shift;

	val = readl_relaxed(mux->reg);

	state = val & SUPER_STATE_MASK;

	BUG_ON((state != super_state(SUPER_STATE_RUN)) &&
	       (state != super_state(SUPER_STATE_IDLE)));
	shift = (state == super_state(SUPER_STATE_IDLE)) ?
		super_state_to_src_shift(mux, SUPER_STATE_IDLE) :
		super_state_to_src_shift(mux, SUPER_STATE_RUN);

	source = (val >> shift) & super_state_to_src_mask(mux);

	/*
	 * If LP_DIV2_BYPASS is not set and PLLX is current parent then
	 * PLLX/2 is the input source to CCLKLP.
	 */
	if ((mux->flags & TEGRA_DIVIDER_2) && !(val & SUPER_LP_DIV2_BYPASS) &&
	    (source == mux->pllx_index))
		source = mux->div2_index;

	return source;
}