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
struct clk_rate_request {unsigned long rate; unsigned long best_parent_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int __clk_determine_rate (struct clk_hw*,struct clk_rate_request*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static int clk_gfx3d_determine_rate(struct clk_hw *hw,
				    struct clk_rate_request *req)
{
	struct clk_rate_request parent_req = { };
	struct clk_hw *p2, *p8, *p9, *xo;
	unsigned long p9_rate;
	int ret;

	xo = clk_hw_get_parent_by_index(hw, 0);
	if (req->rate == clk_hw_get_rate(xo)) {
		req->best_parent_hw = xo;
		return 0;
	}

	p9 = clk_hw_get_parent_by_index(hw, 2);
	p2 = clk_hw_get_parent_by_index(hw, 3);
	p8 = clk_hw_get_parent_by_index(hw, 4);

	/* PLL9 is a fixed rate PLL */
	p9_rate = clk_hw_get_rate(p9);

	parent_req.rate = req->rate = min(req->rate, p9_rate);
	if (req->rate == p9_rate) {
		req->rate = req->best_parent_rate = p9_rate;
		req->best_parent_hw = p9;
		return 0;
	}

	if (req->best_parent_hw == p9) {
		/* Are we going back to a previously used rate? */
		if (clk_hw_get_rate(p8) == req->rate)
			req->best_parent_hw = p8;
		else
			req->best_parent_hw = p2;
	} else if (req->best_parent_hw == p8) {
		req->best_parent_hw = p2;
	} else {
		req->best_parent_hw = p8;
	}

	ret = __clk_determine_rate(req->best_parent_hw, &parent_req);
	if (ret)
		return ret;

	req->rate = req->best_parent_rate = parent_req.rate;

	return 0;
}