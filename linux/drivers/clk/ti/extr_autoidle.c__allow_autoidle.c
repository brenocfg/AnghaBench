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
typedef  int u32 ;
struct clk_ti_autoidle {int flags; int shift; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int AUTOIDLE_LOW ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static void _allow_autoidle(struct clk_ti_autoidle *clk)
{
	u32 val;

	val = ti_clk_ll_ops->clk_readl(&clk->reg);

	if (clk->flags & AUTOIDLE_LOW)
		val &= ~(1 << clk->shift);
	else
		val |= (1 << clk->shift);

	ti_clk_ll_ops->clk_writel(val, &clk->reg);
}