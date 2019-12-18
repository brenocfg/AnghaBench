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
struct clk_hw {int dummy; } ;
struct clk_divider {int /*<<< orphan*/  flags; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 long DIV_ROUND_UP_ULL (int,int) ; 
 int clk_half_divider_bestdiv (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 

__attribute__((used)) static long clk_half_divider_round_rate(struct clk_hw *hw, unsigned long rate,
					unsigned long *prate)
{
	struct clk_divider *divider = to_clk_divider(hw);
	int div;

	div = clk_half_divider_bestdiv(hw, rate, prate,
				       divider->width,
				       divider->flags);

	return DIV_ROUND_UP_ULL(((u64)*prate * 2), div * 2 + 3);
}