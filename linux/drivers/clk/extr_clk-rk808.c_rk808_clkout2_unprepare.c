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
 int /*<<< orphan*/  rk808_clkout2_enable (struct clk_hw*,int) ; 

__attribute__((used)) static void rk808_clkout2_unprepare(struct clk_hw *hw)
{
	rk808_clkout2_enable(hw, false);
}