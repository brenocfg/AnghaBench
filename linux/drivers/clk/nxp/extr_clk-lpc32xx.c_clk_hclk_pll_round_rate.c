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
struct lpc32xx_pll_clk {int m_div; int n_div; int p_div; int /*<<< orphan*/  mode; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  PLL_DIRECT ; 
 int /*<<< orphan*/  PLL_NON_INTEGER ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int div64_u64 (int,int) ; 
 scalar_t__ pll_is_valid (int,int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned long) ; 
 struct lpc32xx_pll_clk* to_lpc32xx_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static long clk_hclk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long *parent_rate)
{
	struct lpc32xx_pll_clk *clk = to_lpc32xx_pll_clk(hw);
	u64 m_i, o = rate, i = *parent_rate, d = (u64)rate << 6;
	u64 m = 0, n = 0, p = 0;
	int p_i, n_i;

	pr_debug("%s: %lu/%lu\n", clk_hw_get_name(hw), *parent_rate, rate);

	if (rate > 266500000)
		return -EINVAL;

	/* Have to check all 20 possibilities to find the minimal M */
	for (p_i = 4; p_i >= 0; p_i--) {
		for (n_i = 4; n_i > 0; n_i--) {
			m_i = div64_u64(o * n_i * (1 << p_i), i);

			/* Check for valid PLL parameter constraints */
			if (!(m_i && m_i <= 256
			      && pll_is_valid(i, n_i, 1000000, 27000000)
			      && pll_is_valid(i * m_i * (1 << p_i), n_i,
					      156000000, 320000000)))
				continue;

			/* Store some intermediate valid parameters */
			if (o * n_i * (1 << p_i) - i * m_i <= d) {
				m = m_i;
				n = n_i;
				p = p_i;
				d = o * n_i * (1 << p_i) - i * m_i;
			}
		}
	}

	if (d == (u64)rate << 6) {
		pr_err("%s: %lu: no valid PLL parameters are found\n",
		       clk_hw_get_name(hw), rate);
		return -EINVAL;
	}

	clk->m_div = m;
	clk->n_div = n;
	clk->p_div = p;

	/* Set only direct or non-integer mode of PLL */
	if (!p)
		clk->mode = PLL_DIRECT;
	else
		clk->mode = PLL_NON_INTEGER;

	o = div64_u64(i * m, n * (1 << p));

	if (!d)
		pr_debug("%s: %lu: found exact match: %llu/%llu/%llu\n",
			 clk_hw_get_name(hw), rate, m, n, p);
	else
		pr_debug("%s: %lu: found closest: %llu/%llu/%llu - %llu\n",
			 clk_hw_get_name(hw), rate, m, n, p, o);

	return o;
}