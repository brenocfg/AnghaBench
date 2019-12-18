#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {scalar_t__ usecount; struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct clk*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local_clk_disable (struct clk*) ; 
 int stub1 (struct clk*,int) ; 

__attribute__((used)) static int local_clk_enable(struct clk *clk)
{
	int ret = 0;

	if (clk->parent)
		ret = local_clk_enable(clk->parent);

	if (ret)
		return ret;

	if ((clk->usecount == 0) && (clk->ops->enable))
		ret = clk->ops->enable(clk, 1);

	if (!ret)
		clk->usecount++;
	else if (clk->parent && clk->parent->ops->enable)
		local_clk_disable(clk->parent);

	return ret;
}