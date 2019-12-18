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
struct meson_clk_pll_data {int flags; int /*<<< orphan*/  frac; } ;

/* Variables and functions */
 int CLK_MESON_PLL_ROUND_CLOSEST ; 
 int /*<<< orphan*/  MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __pll_round_closest_mult(struct meson_clk_pll_data *pll)
{
	if ((pll->flags & CLK_MESON_PLL_ROUND_CLOSEST) &&
	    !MESON_PARM_APPLICABLE(&pll->frac))
		return 1;

	return 0;
}