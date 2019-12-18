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

/* Variables and functions */
 int AST2500_HPLL_BYPASS_EN ; 
 struct clk_hw* clk_hw_register_fixed_factor (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static struct clk_hw *aspeed_ast2500_calc_pll(const char *name, u32 val)
{
	unsigned int mult, div;

	if (val & AST2500_HPLL_BYPASS_EN) {
		/* Pass through mode */
		mult = div = 1;
	} else {
		/* F = clkin * [(M+1) / (N+1)] / (P + 1) */
		u32 p = (val >> 13) & 0x3f;
		u32 m = (val >> 5) & 0xff;
		u32 n = val & 0x1f;

		mult = (m + 1) / (n + 1);
		div = p + 1;
	}

	return clk_hw_register_fixed_factor(NULL, name, "clkin", 0,
			mult, div);
}