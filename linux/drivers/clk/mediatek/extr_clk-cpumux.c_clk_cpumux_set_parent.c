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
struct mtk_clk_cpumux {int shift; int mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_clk_cpumux* to_mtk_clk_cpumux (struct clk_hw*) ; 

__attribute__((used)) static int clk_cpumux_set_parent(struct clk_hw *hw, u8 index)
{
	struct mtk_clk_cpumux *mux = to_mtk_clk_cpumux(hw);
	u32 mask, val;

	val = index << mux->shift;
	mask = mux->mask << mux->shift;

	return regmap_update_bits(mux->regmap, mux->reg, mask, val);
}