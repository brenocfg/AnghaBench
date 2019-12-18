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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct krait_mux_clk {int reparent; int /*<<< orphan*/  en_mask; int /*<<< orphan*/  parent_map; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ __clk_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __krait_mux_set_sel (struct krait_mux_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_mux_index_to_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct krait_mux_clk* to_krait_mux_clk (struct clk_hw*) ; 

__attribute__((used)) static int krait_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct krait_mux_clk *mux = to_krait_mux_clk(hw);
	u32 sel;

	sel = clk_mux_index_to_val(mux->parent_map, 0, index);
	mux->en_mask = sel;
	/* Don't touch mux if CPU is off as it won't work */
	if (__clk_is_enabled(hw->clk))
		__krait_mux_set_sel(mux, sel);

	mux->reparent = true;

	return 0;
}