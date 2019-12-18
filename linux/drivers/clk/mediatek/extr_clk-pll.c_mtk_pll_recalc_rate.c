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
struct mtk_clk_pll {TYPE_1__* data; int /*<<< orphan*/  pcw_addr; int /*<<< orphan*/  pd_addr; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int pd_shift; int pcw_shift; scalar_t__ pcwbits; } ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int POSTDIV_MASK ; 
 unsigned long __mtk_pll_recalc_rate (struct mtk_clk_pll*,unsigned long,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct mtk_clk_pll* to_mtk_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long mtk_pll_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 postdiv;
	u32 pcw;

	postdiv = (readl(pll->pd_addr) >> pll->data->pd_shift) & POSTDIV_MASK;
	postdiv = 1 << postdiv;

	pcw = readl(pll->pcw_addr) >> pll->data->pcw_shift;
	pcw &= GENMASK(pll->data->pcwbits - 1, 0);

	return __mtk_pll_recalc_rate(pll, parent_rate, pcw, postdiv);
}