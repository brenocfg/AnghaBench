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
typedef  int u32 ;
struct krait_mux_clk {int shift; int mask; int en_mask; int /*<<< orphan*/  parent_map; int /*<<< orphan*/  offset; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_mux_val_to_index (struct clk_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int krait_get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 struct krait_mux_clk* to_krait_mux_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 krait_mux_get_parent(struct clk_hw *hw)
{
	struct krait_mux_clk *mux = to_krait_mux_clk(hw);
	u32 sel;

	sel = krait_get_l2_indirect_reg(mux->offset);
	sel >>= mux->shift;
	sel &= mux->mask;
	mux->en_mask = sel;

	return clk_mux_val_to_index(hw, mux->parent_map, 0, sel);
}