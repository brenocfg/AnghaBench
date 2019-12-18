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
typedef  int u32 ;
struct krait_div2_clk {int shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int krait_get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 struct krait_div2_clk* to_krait_div2_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
krait_div2_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct krait_div2_clk *d = to_krait_div2_clk(hw);
	u32 mask = BIT(d->width) - 1;
	u32 div;

	div = krait_get_l2_indirect_reg(d->offset);
	div >>= d->shift;
	div &= mask;
	div = (div + 1) * 2;

	return DIV_ROUND_UP(parent_rate, div);
}