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
typedef  int u8 ;
typedef  int u64 ;
struct clk_pfdv2 {int frac_off; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_PFDV2_FRAC_MASK ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pfdv2* to_clk_pfdv2 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pfdv2_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	u64 tmp = parent_rate;
	u8 frac;

	frac = (readl_relaxed(pfd->reg) >> pfd->frac_off)
		& CLK_PFDV2_FRAC_MASK;

	if (!frac) {
		pr_debug("clk_pfdv2: %s invalid pfd frac value 0\n",
			 clk_hw_get_name(hw));
		return 0;
	}

	tmp *= 18;
	do_div(tmp, frac);

	return tmp;
}