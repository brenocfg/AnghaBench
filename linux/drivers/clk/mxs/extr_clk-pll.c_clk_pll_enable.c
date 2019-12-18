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
struct clk_pll {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLR ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int clk_pll_enable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	writel_relaxed(1 << 31, pll->base + CLR);

	return 0;
}