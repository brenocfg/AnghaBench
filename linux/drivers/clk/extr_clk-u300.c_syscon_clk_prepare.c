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
struct clk_syscon {scalar_t__ reset; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  syscon_block_reset_disable (struct clk_syscon*) ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 

__attribute__((used)) static int syscon_clk_prepare(struct clk_hw *hw)
{
	struct clk_syscon *sclk = to_syscon(hw);

	/* If the block is in reset, bring it out */
	if (sclk->reset)
		syscon_block_reset_disable(sclk);
	return 0;
}