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
struct clk_fractional_divider {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister (struct clk_hw*) ; 
 int /*<<< orphan*/  kfree (struct clk_fractional_divider*) ; 
 struct clk_fractional_divider* to_clk_fd (struct clk_hw*) ; 

void clk_hw_unregister_fractional_divider(struct clk_hw *hw)
{
	struct clk_fractional_divider *fd;

	fd = to_clk_fd(hw);

	clk_hw_unregister(hw);
	kfree(fd);
}