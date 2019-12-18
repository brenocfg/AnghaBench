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
struct clk_pll {int type; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
#define  PLL_TYPE_VT8500 131 
#define  PLL_TYPE_WM8650 130 
#define  PLL_TYPE_WM8750 129 
#define  PLL_TYPE_WM8850 128 
 unsigned long VT8500_PLL_DIV (int /*<<< orphan*/ ) ; 
 unsigned long VT8500_PLL_MUL (int /*<<< orphan*/ ) ; 
 unsigned long WM8650_PLL_DIV (int /*<<< orphan*/ ) ; 
 unsigned long WM8650_PLL_MUL (int /*<<< orphan*/ ) ; 
 unsigned long WM8750_PLL_DIV (int /*<<< orphan*/ ) ; 
 unsigned long WM8750_PLL_MUL (int /*<<< orphan*/ ) ; 
 unsigned long WM8850_PLL_DIV (int /*<<< orphan*/ ) ; 
 unsigned long WM8850_PLL_MUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long vtwm_pll_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	u32 pll_val = readl(pll->reg);
	unsigned long pll_freq;

	switch (pll->type) {
	case PLL_TYPE_VT8500:
		pll_freq = parent_rate * VT8500_PLL_MUL(pll_val);
		pll_freq /= VT8500_PLL_DIV(pll_val);
		break;
	case PLL_TYPE_WM8650:
		pll_freq = parent_rate * WM8650_PLL_MUL(pll_val);
		pll_freq /= WM8650_PLL_DIV(pll_val);
		break;
	case PLL_TYPE_WM8750:
		pll_freq = parent_rate * WM8750_PLL_MUL(pll_val);
		pll_freq /= WM8750_PLL_DIV(pll_val);
		break;
	case PLL_TYPE_WM8850:
		pll_freq = parent_rate * WM8850_PLL_MUL(pll_val);
		pll_freq /= WM8850_PLL_DIV(pll_val);
		break;
	default:
		pll_freq = 0;
	}

	return pll_freq;
}