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
struct clk_regmap_mux_div {int /*<<< orphan*/  hid_width; } ;
struct clk_rate_request {unsigned long rate; unsigned long best_parent_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,unsigned int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 scalar_t__ is_better_rate (unsigned long,unsigned long,unsigned long) ; 
 unsigned long mult_frac (unsigned long,int,unsigned int) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static int mux_div_determine_rate(struct clk_hw *hw,
				  struct clk_rate_request *req)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);
	unsigned int i, div, max_div;
	unsigned long actual_rate, best_rate = 0;
	unsigned long req_rate = req->rate;

	for (i = 0; i < clk_hw_get_num_parents(hw); i++) {
		struct clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		unsigned long parent_rate = clk_hw_get_rate(parent);

		max_div = BIT(md->hid_width) - 1;
		for (div = 1; div < max_div; div++) {
			parent_rate = mult_frac(req_rate, div, 2);
			parent_rate = clk_hw_round_rate(parent, parent_rate);
			actual_rate = mult_frac(parent_rate, 2, div);

			if (is_better_rate(req_rate, best_rate, actual_rate)) {
				best_rate = actual_rate;
				req->rate = best_rate;
				req->best_parent_rate = parent_rate;
				req->best_parent_hw = parent;
			}

			if (actual_rate < req_rate || best_rate <= req_rate)
				break;
		}
	}

	if (!best_rate)
		return -EINVAL;

	return 0;
}