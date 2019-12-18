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
struct pll_clock {int /*<<< orphan*/  pllcr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readb (int /*<<< orphan*/ ) ; 
 struct pll_clock* to_pll_clock (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct pll_clock *pll_clock = to_pll_clock(hw);
	int mul = 1 << (readb(pll_clock->pllcr) & 3);

	return parent_rate * mul;
}