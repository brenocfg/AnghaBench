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
typedef  int u32 ;
struct clk_regmap_mux_div {int* parent_map; int div; int src; int /*<<< orphan*/  hid_width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,unsigned int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 scalar_t__ is_better_rate (unsigned long,unsigned long,unsigned long) ; 
 unsigned long mult_frac (unsigned long,int,int) ; 
 int mux_div_set_src_div (struct clk_regmap_mux_div*,int,int) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static int __mux_div_set_rate_and_parent(struct clk_hw *hw, unsigned long rate,
					 unsigned long prate, u32 src)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);
	int ret;
	u32 div, max_div, best_src = 0, best_div = 0;
	unsigned int i;
	unsigned long actual_rate, best_rate = 0;

	for (i = 0; i < clk_hw_get_num_parents(hw); i++) {
		struct clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		unsigned long parent_rate = clk_hw_get_rate(parent);

		max_div = BIT(md->hid_width) - 1;
		for (div = 1; div < max_div; div++) {
			parent_rate = mult_frac(rate, div, 2);
			parent_rate = clk_hw_round_rate(parent, parent_rate);
			actual_rate = mult_frac(parent_rate, 2, div);

			if (is_better_rate(rate, best_rate, actual_rate)) {
				best_rate = actual_rate;
				best_src = md->parent_map[i];
				best_div = div - 1;
			}

			if (actual_rate < rate || best_rate <= rate)
				break;
		}
	}

	ret = mux_div_set_src_div(md, best_src, best_div);
	if (!ret) {
		md->div = best_div;
		md->src = best_src;
	}

	return ret;
}