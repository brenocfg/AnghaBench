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
struct clk_hw {int dummy; } ;
struct alchemy_auxpll_clk {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 struct alchemy_auxpll_clk* to_auxpll_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long alchemy_clk_aux_recalc(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct alchemy_auxpll_clk *a = to_auxpll_clk(hw);

	return (alchemy_rdsys(a->reg) & 0xff) * parent_rate;
}