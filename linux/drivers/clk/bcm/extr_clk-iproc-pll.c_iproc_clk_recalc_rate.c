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
typedef  unsigned int u32 ;
struct iproc_pll {scalar_t__ control_base; } ;
struct TYPE_2__ {unsigned int shift; int /*<<< orphan*/  width; scalar_t__ offset; } ;
struct iproc_clk_ctrl {int flags; TYPE_1__ mdiv; } ;
struct iproc_clk {struct iproc_pll* pll; struct iproc_clk_ctrl* ctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int IPROC_CLK_MCLK_DIV_BY_2 ; 
 unsigned int bit_mask (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long iproc_clk_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;
	unsigned int mdiv;
	unsigned long rate;

	if (parent_rate == 0)
		return 0;

	val = readl(pll->control_base + ctrl->mdiv.offset);
	mdiv = (val >> ctrl->mdiv.shift) & bit_mask(ctrl->mdiv.width);
	if (mdiv == 0)
		mdiv = 256;

	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		rate = parent_rate / (mdiv * 2);
	else
		rate = parent_rate / mdiv;

	return rate;
}