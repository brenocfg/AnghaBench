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
struct clk_pll {int type; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_TYPE_VT8500 131 
#define  PLL_TYPE_WM8650 130 
#define  PLL_TYPE_WM8750 129 
#define  PLL_TYPE_WM8850 128 
 long VT8500_BITS_TO_FREQ (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long WM8650_BITS_TO_FREQ (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long WM8750_BITS_TO_FREQ (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long WM8850_BITS_TO_FREQ (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 
 int vt8500_find_pll_bits (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wm8650_find_pll_bits (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wm8750_find_pll_bits (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wm8850_find_pll_bits (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long vtwm_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	u32 filter, mul, div1, div2;
	long round_rate;
	int ret;

	switch (pll->type) {
	case PLL_TYPE_VT8500:
		ret = vt8500_find_pll_bits(rate, *prate, &mul, &div1);
		if (!ret)
			round_rate = VT8500_BITS_TO_FREQ(*prate, mul, div1);
		break;
	case PLL_TYPE_WM8650:
		ret = wm8650_find_pll_bits(rate, *prate, &mul, &div1, &div2);
		if (!ret)
			round_rate = WM8650_BITS_TO_FREQ(*prate, mul, div1, div2);
		break;
	case PLL_TYPE_WM8750:
		ret = wm8750_find_pll_bits(rate, *prate, &filter, &mul, &div1, &div2);
		if (!ret)
			round_rate = WM8750_BITS_TO_FREQ(*prate, mul, div1, div2);
		break;
	case PLL_TYPE_WM8850:
		ret = wm8850_find_pll_bits(rate, *prate, &mul, &div1, &div2);
		if (!ret)
			round_rate = WM8850_BITS_TO_FREQ(*prate, mul, div1, div2);
		break;
	default:
		ret = -EINVAL;
	}

	if (ret)
		return ret;

	return round_rate;
}