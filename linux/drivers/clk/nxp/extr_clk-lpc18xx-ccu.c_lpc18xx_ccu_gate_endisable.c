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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct clk_gate {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int LPC18XX_CCU_AUTO ; 
 int LPC18XX_CCU_DIV ; 
 int LPC18XX_CCU_DIVSTAT ; 
 int LPC18XX_CCU_RUN ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_gate* to_clk_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_ccu_gate_endisable(struct clk_hw *hw, bool enable)
{
	struct clk_gate *gate = to_clk_gate(hw);
	u32 val;

	/*
	 * Divider field is write only, so divider stat field must
	 * be read so divider field can be set accordingly.
	 */
	val = readl(gate->reg);
	if (val & LPC18XX_CCU_DIVSTAT)
		val |= LPC18XX_CCU_DIV;

	if (enable) {
		val |= LPC18XX_CCU_RUN;
	} else {
		/*
		 * To safely disable a branch clock a squence of two separate
		 * writes must be used. First write should set the AUTO bit
		 * and the next write should clear the RUN bit.
		 */
		val |= LPC18XX_CCU_AUTO;
		writel(val, gate->reg);

		val &= ~LPC18XX_CCU_RUN;
	}

	writel(val, gate->reg);

	return 0;
}