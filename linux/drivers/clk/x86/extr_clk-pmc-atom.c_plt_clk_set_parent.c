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
typedef  int /*<<< orphan*/  u8 ;
struct clk_plt {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_MASK_CLK_FREQ ; 
 int /*<<< orphan*/  plt_clk_reg_update (struct clk_plt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plt_parent_to_reg (int /*<<< orphan*/ ) ; 
 struct clk_plt* to_clk_plt (struct clk_hw*) ; 

__attribute__((used)) static int plt_clk_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_plt *clk = to_clk_plt(hw);

	plt_clk_reg_update(clk, PMC_MASK_CLK_FREQ, plt_parent_to_reg(index));

	return 0;
}