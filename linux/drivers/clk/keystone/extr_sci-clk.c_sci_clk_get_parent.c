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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sci_clk {scalar_t__ clk_id; int /*<<< orphan*/  dev_id; TYPE_1__* provider; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int (* get_parent ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sci; TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 struct sci_clk* to_sci_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 sci_clk_get_parent(struct clk_hw *hw)
{
	struct sci_clk *clk = to_sci_clk(hw);
	u32 parent_id = 0;
	int ret;

	ret = clk->provider->ops->get_parent(clk->provider->sci, clk->dev_id,
					     clk->clk_id, (void *)&parent_id);
	if (ret) {
		dev_err(clk->provider->dev,
			"get-parent failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		return 0;
	}

	parent_id = parent_id - clk->clk_id - 1;

	return (u8)parent_id;
}