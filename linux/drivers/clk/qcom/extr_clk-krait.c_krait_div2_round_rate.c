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

/* Variables and functions */
 long DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long krait_div2_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *parent_rate)
{
	*parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw), rate * 2);
	return DIV_ROUND_UP(*parent_rate, 2);
}