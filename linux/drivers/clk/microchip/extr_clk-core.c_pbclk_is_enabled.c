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
struct pic32_periph_clk {int /*<<< orphan*/  ctrl_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PB_DIV_ENABLE ; 
 struct pic32_periph_clk* clkhw_to_pbclk (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pbclk_is_enabled(struct clk_hw *hw)
{
	struct pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	return readl(pb->ctrl_reg) & PB_DIV_ENABLE;
}