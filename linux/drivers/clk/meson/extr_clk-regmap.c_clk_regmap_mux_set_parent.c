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
struct clk_regmap_mux_data {int mask; int shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; int /*<<< orphan*/  table; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_regmap_mux_data* clk_get_regmap_mux_data (struct clk_regmap*) ; 
 unsigned int clk_mux_index_to_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int clk_regmap_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct clk_regmap_mux_data *mux = clk_get_regmap_mux_data(clk);
	unsigned int val = clk_mux_index_to_val(mux->table, mux->flags, index);

	return regmap_update_bits(clk->map, mux->offset,
				  mux->mask << mux->shift,
				  val << mux->shift);
}