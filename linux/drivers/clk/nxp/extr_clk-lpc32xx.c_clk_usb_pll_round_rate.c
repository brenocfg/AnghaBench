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
typedef  int u64 ;
struct lpc32xx_pll_clk {int n_div; int m_div; int p_div; int /*<<< orphan*/  mode; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  PLL_NON_INTEGER ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int /*<<< orphan*/ ) ; 
 int clk_hw_get_rate (struct clk_hw*) ; 
 void* div64_u64 (int,int) ; 
 scalar_t__ pll_is_valid (int,int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct lpc32xx_pll_clk* to_lpc32xx_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static long clk_usb_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long *parent_rate)
{
	struct lpc32xx_pll_clk *clk = to_lpc32xx_pll_clk(hw);
	struct clk_hw *usb_div_hw, *osc_hw;
	u64 d_i, n_i, m, o;

	pr_debug("%s: %lu/%lu\n", clk_hw_get_name(hw), *parent_rate, rate);

	/*
	 * The only supported USB clock is 48MHz, with PLL internal constraints
	 * on Fclkin, Fcco and Fref this implies that Fcco must be 192MHz
	 * and post-divider must be 4, this slightly simplifies calculation of
	 * USB divider, USB PLL N and M parameters.
	 */
	if (rate != 48000000)
		return -EINVAL;

	/* USB divider clock */
	usb_div_hw = clk_hw_get_parent_by_index(hw, 0);
	if (!usb_div_hw)
		return -EINVAL;

	/* Main oscillator clock */
	osc_hw = clk_hw_get_parent_by_index(usb_div_hw, 0);
	if (!osc_hw)
		return -EINVAL;
	o = clk_hw_get_rate(osc_hw);	/* must be in range 1..20 MHz */

	/* Check if valid USB divider and USB PLL parameters exists */
	for (d_i = 16; d_i >= 1; d_i--) {
		for (n_i = 1; n_i <= 4; n_i++) {
			m = div64_u64(192000000 * d_i * n_i, o);
			if (!(m && m <= 256
			      && m * o == 192000000 * d_i * n_i
			      && pll_is_valid(o, d_i, 1000000, 20000000)
			      && pll_is_valid(o, d_i * n_i, 1000000, 27000000)))
				continue;

			clk->n_div = n_i;
			clk->m_div = m;
			clk->p_div = 2;
			clk->mode = PLL_NON_INTEGER;
			*parent_rate = div64_u64(o, d_i);

			return rate;
		}
	}

	return -EINVAL;
}