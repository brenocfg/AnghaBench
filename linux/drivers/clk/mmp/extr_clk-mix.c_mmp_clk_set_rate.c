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
struct mmp_clk_mix_clk_table {scalar_t__ valid; int parent_index; unsigned int divisor; } ;
struct mmp_clk_mix {int table_size; struct mmp_clk_mix_clk_table* table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _get_div_val (struct mmp_clk_mix*,unsigned int) ; 
 int /*<<< orphan*/  _get_mux_val (struct mmp_clk_mix*,int) ; 
 int _set_rate (struct mmp_clk_mix*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 struct mmp_clk_mix* to_clk_mix (struct clk_hw*) ; 

__attribute__((used)) static int mmp_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long best_parent_rate)
{
	struct mmp_clk_mix *mix = to_clk_mix(hw);
	struct mmp_clk_mix_clk_table *item;
	unsigned long parent_rate;
	unsigned int best_divisor;
	struct clk_hw *parent;
	int i;

	best_divisor = best_parent_rate / rate;

	if (mix->table) {
		for (i = 0; i < mix->table_size; i++) {
			item = &mix->table[i];
			if (item->valid == 0)
				continue;
			parent = clk_hw_get_parent_by_index(hw,
							item->parent_index);
			parent_rate = clk_hw_get_rate(parent);
			if (parent_rate == best_parent_rate
				&& item->divisor == best_divisor)
				break;
		}
		if (i < mix->table_size)
			return _set_rate(mix,
					_get_mux_val(mix, item->parent_index),
					_get_div_val(mix, item->divisor),
					1, 1);
		else
			return -EINVAL;
	} else {
		for (i = 0; i < clk_hw_get_num_parents(hw); i++) {
			parent = clk_hw_get_parent_by_index(hw, i);
			parent_rate = clk_hw_get_rate(parent);
			if (parent_rate == best_parent_rate)
				break;
		}
		if (i < clk_hw_get_num_parents(hw))
			return _set_rate(mix, _get_mux_val(mix, i),
					_get_div_val(mix, best_divisor), 1, 1);
		else
			return -EINVAL;
	}
}