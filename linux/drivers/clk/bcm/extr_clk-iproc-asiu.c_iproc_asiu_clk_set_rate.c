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
struct TYPE_2__ {int en_shift; int high_shift; int low_shift; scalar_t__ offset; int /*<<< orphan*/  low_width; int /*<<< orphan*/  high_width; } ;
struct iproc_asiu_clk {TYPE_1__ div; struct iproc_asiu* asiu; } ;
struct iproc_asiu {scalar_t__ div_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 int bit_mask (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct iproc_asiu_clk* to_asiu_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int iproc_asiu_clk_set_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long parent_rate)
{
	struct iproc_asiu_clk *clk = to_asiu_clk(hw);
	struct iproc_asiu *asiu = clk->asiu;
	unsigned int div, div_h, div_l;
	u32 val;

	if (rate == 0 || parent_rate == 0)
		return -EINVAL;

	/* simply disable the divisor if one wants the same rate as parent */
	if (rate == parent_rate) {
		val = readl(asiu->div_base + clk->div.offset);
		val &= ~(1 << clk->div.en_shift);
		writel(val, asiu->div_base + clk->div.offset);
		return 0;
	}

	div = DIV_ROUND_UP(parent_rate, rate);
	if (div < 2)
		return -EINVAL;

	div_h = div_l = div >> 1;
	div_h--;
	div_l--;

	val = readl(asiu->div_base + clk->div.offset);
	val |= 1 << clk->div.en_shift;
	if (div_h) {
		val &= ~(bit_mask(clk->div.high_width)
			 << clk->div.high_shift);
		val |= div_h << clk->div.high_shift;
	} else {
		val &= ~(bit_mask(clk->div.high_width)
			 << clk->div.high_shift);
	}
	if (div_l) {
		val &= ~(bit_mask(clk->div.low_width) << clk->div.low_shift);
		val |= div_l << clk->div.low_shift;
	} else {
		val &= ~(bit_mask(clk->div.low_width) << clk->div.low_shift);
	}
	writel(val, asiu->div_base + clk->div.offset);

	return 0;
}