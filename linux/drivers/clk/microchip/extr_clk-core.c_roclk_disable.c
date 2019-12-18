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
struct pic32_ref_osc {int /*<<< orphan*/  ctrl_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int REFO_OE ; 
 int REFO_ON ; 
 struct pic32_ref_osc* clkhw_to_refosc (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void roclk_disable(struct clk_hw *hw)
{
	struct pic32_ref_osc *refo = clkhw_to_refosc(hw);

	writel(REFO_ON | REFO_OE, PIC32_CLR(refo->ctrl_reg));
}