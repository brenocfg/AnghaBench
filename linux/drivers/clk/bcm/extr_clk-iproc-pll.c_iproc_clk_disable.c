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
struct iproc_pll {scalar_t__ control_base; } ;
struct TYPE_2__ {int enable_shift; scalar_t__ offset; } ;
struct iproc_clk_ctrl {int flags; TYPE_1__ enable; } ;
struct iproc_clk {struct iproc_pll* pll; struct iproc_clk_ctrl* ctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int IPROC_CLK_AON ; 
 int /*<<< orphan*/  iproc_pll_write (struct iproc_pll*,scalar_t__,scalar_t__,int) ; 
 int readl (scalar_t__) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static void iproc_clk_disable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;

	if (ctrl->flags & IPROC_CLK_AON)
		return;

	val = readl(pll->control_base + ctrl->enable.offset);
	val |= 1 << ctrl->enable.enable_shift;
	iproc_pll_write(pll, pll->control_base, ctrl->enable.offset, val);
}