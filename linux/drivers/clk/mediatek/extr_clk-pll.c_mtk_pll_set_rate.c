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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_pll_calc_values (struct mtk_clk_pll*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mtk_pll_set_rate_regs (struct mtk_clk_pll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_clk_pll* to_mtk_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int mtk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 pcw = 0;
	u32 postdiv;

	mtk_pll_calc_values(pll, &pcw, &postdiv, rate, parent_rate);
	mtk_pll_set_rate_regs(pll, pcw, postdiv);

	return 0;
}