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
struct scmi_clk {int /*<<< orphan*/  id; TYPE_2__* handle; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* clk_ops; } ;
struct TYPE_3__ {int (* rate_get ) (TYPE_2__*,int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct scmi_clk* to_scmi_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long scmi_clk_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	int ret;
	u64 rate;
	struct scmi_clk *clk = to_scmi_clk(hw);

	ret = clk->handle->clk_ops->rate_get(clk->handle, clk->id, &rate);
	if (ret)
		return 0;
	return rate;
}