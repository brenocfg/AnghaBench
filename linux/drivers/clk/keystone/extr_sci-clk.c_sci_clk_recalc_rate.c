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
typedef  unsigned long u64 ;
struct sci_clk {int /*<<< orphan*/  clk_id; int /*<<< orphan*/  dev_id; TYPE_2__* provider; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sci; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_freq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 struct sci_clk* to_sci_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long sci_clk_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct sci_clk *clk = to_sci_clk(hw);
	u64 freq;
	int ret;

	ret = clk->provider->ops->get_freq(clk->provider->sci, clk->dev_id,
					   clk->clk_id, &freq);
	if (ret) {
		dev_err(clk->provider->dev,
			"recalc-rate failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		return 0;
	}

	return freq;
}