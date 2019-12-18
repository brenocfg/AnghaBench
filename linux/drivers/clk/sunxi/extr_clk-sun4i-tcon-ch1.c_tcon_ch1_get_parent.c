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
typedef  int u8 ;
typedef  int u32 ;
struct tcon_ch1_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int TCON_CH1_SCLK2_MUX_MASK ; 
 int TCON_CH1_SCLK2_MUX_SHIFT ; 
 struct tcon_ch1_clk* hw_to_tclk (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 tcon_ch1_get_parent(struct clk_hw *hw)
{
	struct tcon_ch1_clk *tclk = hw_to_tclk(hw);
	u32 reg;

	reg = readl(tclk->reg) >> TCON_CH1_SCLK2_MUX_SHIFT;
	reg &= reg >> TCON_CH1_SCLK2_MUX_MASK;

	return reg;
}