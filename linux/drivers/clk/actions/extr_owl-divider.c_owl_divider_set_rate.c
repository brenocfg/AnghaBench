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
struct owl_divider {int /*<<< orphan*/  div_hw; int /*<<< orphan*/  common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct owl_divider* hw_to_owl_divider (struct clk_hw*) ; 
 int owl_divider_helper_set_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int owl_divider_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct owl_divider *div = hw_to_owl_divider(hw);

	return owl_divider_helper_set_rate(&div->common, &div->div_hw,
					rate, parent_rate);
}