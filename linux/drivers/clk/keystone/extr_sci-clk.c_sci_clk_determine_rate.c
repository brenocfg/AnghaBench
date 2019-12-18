#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sci_clk {int /*<<< orphan*/  clk_id; int /*<<< orphan*/  dev_id; TYPE_1__* provider; } ;
struct clk_rate_request {int /*<<< orphan*/  rate; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int (* get_best_match_freq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sci; TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sci_clk* to_sci_clk (struct clk_hw*) ; 

__attribute__((used)) static int sci_clk_determine_rate(struct clk_hw *hw,
				  struct clk_rate_request *req)
{
	struct sci_clk *clk = to_sci_clk(hw);
	int ret;
	u64 new_rate;

	ret = clk->provider->ops->get_best_match_freq(clk->provider->sci,
						      clk->dev_id,
						      clk->clk_id,
						      req->min_rate,
						      req->rate,
						      req->max_rate,
						      &new_rate);
	if (ret) {
		dev_err(clk->provider->dev,
			"determine-rate failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		return ret;
	}

	req->rate = new_rate;

	return 0;
}