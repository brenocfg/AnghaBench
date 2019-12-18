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
struct clk_gpio {int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 struct clk_gpio* to_clk_gpio (struct clk_hw*) ; 

__attribute__((used)) static int clk_sleeping_gpio_gate_is_prepared(struct clk_hw *hw)
{
	struct clk_gpio *clk = to_clk_gpio(hw);

	return gpiod_get_value_cansleep(clk->gpiod);
}