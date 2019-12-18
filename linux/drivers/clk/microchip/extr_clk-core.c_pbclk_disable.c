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
 int /*<<< orphan*/  PB_DIV_ENABLE ; 
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 struct pic32_periph_clk* clkhw_to_pbclk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pbclk_disable(struct clk_hw *hw)
{
	struct pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	writel(PB_DIV_ENABLE, PIC32_CLR(pb->ctrl_reg));
}