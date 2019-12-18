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
struct factors_request {unsigned long rate; int parent_index; unsigned long parent_rate; } ;
struct clk_rate_request {unsigned long rate; unsigned long best_parent_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;
struct clk_factors {int /*<<< orphan*/  (* get_factors ) (struct factors_request*) ;} ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 int EINVAL ; 
 int clk_hw_get_flags (struct clk_hw*) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (struct clk_hw*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct factors_request*) ; 
 struct clk_factors* to_clk_factors (struct clk_hw*) ; 

__attribute__((used)) static int clk_factors_determine_rate(struct clk_hw *hw,
				      struct clk_rate_request *req)
{
	struct clk_factors *factors = to_clk_factors(hw);
	struct clk_hw *parent, *best_parent = NULL;
	int i, num_parents;
	unsigned long parent_rate, best = 0, child_rate, best_child_rate = 0;

	/* find the parent that can help provide the fastest rate <= rate */
	num_parents = clk_hw_get_num_parents(hw);
	for (i = 0; i < num_parents; i++) {
		struct factors_request factors_req = {
			.rate = req->rate,
			.parent_index = i,
		};
		parent = clk_hw_get_parent_by_index(hw, i);
		if (!parent)
			continue;
		if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
			parent_rate = clk_hw_round_rate(parent, req->rate);
		else
			parent_rate = clk_hw_get_rate(parent);

		factors_req.parent_rate = parent_rate;
		factors->get_factors(&factors_req);
		child_rate = factors_req.rate;

		if (child_rate <= req->rate && child_rate > best_child_rate) {
			best_parent = parent;
			best = parent_rate;
			best_child_rate = child_rate;
		}
	}

	if (!best_parent)
		return -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best_child_rate;

	return 0;
}