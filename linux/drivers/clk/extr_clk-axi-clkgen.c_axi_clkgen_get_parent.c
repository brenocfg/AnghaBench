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
typedef  unsigned int u8 ;
struct clk_hw {int dummy; } ;
struct axi_clkgen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_CLKGEN_V2_REG_CLKSEL ; 
 int /*<<< orphan*/  axi_clkgen_read (struct axi_clkgen*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct axi_clkgen* clk_hw_to_axi_clkgen (struct clk_hw*) ; 

__attribute__((used)) static u8 axi_clkgen_get_parent(struct clk_hw *clk_hw)
{
	struct axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);
	unsigned int parent;

	axi_clkgen_read(axi_clkgen, AXI_CLKGEN_V2_REG_CLKSEL, &parent);

	return parent;
}