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
struct socfpga_gate_clk {int bypass_shift; scalar_t__ bypass_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 struct socfpga_gate_clk* to_socfpga_gate_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 socfpga_gate_get_parent(struct clk_hw *hwclk)
{
	struct socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 mask;
	u8 parent = 0;

	if (socfpgaclk->bypass_reg) {
		mask = (0x1 << socfpgaclk->bypass_shift);
		parent = ((readl(socfpgaclk->bypass_reg) & mask) >>
			  socfpgaclk->bypass_shift);
	}
	return parent;
}