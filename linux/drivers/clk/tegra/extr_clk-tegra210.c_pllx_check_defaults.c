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
struct tegra_clk_pll {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int PLLX_MISC0_DEFAULT_VALUE ; 
 int PLLX_MISC0_LOCK_ENABLE ; 
 int PLLX_MISC0_WRITE_MASK ; 
 int PLLX_MISC1_DEFAULT_VALUE ; 
 int PLLX_MISC1_WRITE_MASK ; 
 int PLLX_MISC2_DEFAULT_VALUE ; 
 int PLLX_MISC2_EN_DYNRAMP ; 
 int PLLX_MISC3_DEFAULT_VALUE ; 
 int PLLX_MISC3_IDDQ ; 
 int PLLX_MISC3_WRITE_MASK ; 
 int PLLX_MISC4_DEFAULT_VALUE ; 
 int PLLX_MISC4_WRITE_MASK ; 
 int PLLX_MISC5_DEFAULT_VALUE ; 
 int PLLX_MISC5_WRITE_MASK ; 
 int /*<<< orphan*/  _pll_misc_chk_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  clk_base ; 

__attribute__((used)) static void pllx_check_defaults(struct tegra_clk_pll *pll)
{
	u32 default_val;

	default_val = PLLX_MISC0_DEFAULT_VALUE;
	/* ignore lock enable */
	_pll_misc_chk_default(clk_base, pll->params, 0, default_val,
			PLLX_MISC0_WRITE_MASK & (~PLLX_MISC0_LOCK_ENABLE));

	default_val = PLLX_MISC1_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, pll->params, 1, default_val,
			PLLX_MISC1_WRITE_MASK);

	/* ignore all but control bit */
	default_val = PLLX_MISC2_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, pll->params, 2,
			default_val, PLLX_MISC2_EN_DYNRAMP);

	default_val = PLLX_MISC3_DEFAULT_VALUE & (~PLLX_MISC3_IDDQ);
	_pll_misc_chk_default(clk_base, pll->params, 3, default_val,
			PLLX_MISC3_WRITE_MASK);

	default_val = PLLX_MISC4_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, pll->params, 4, default_val,
			PLLX_MISC4_WRITE_MASK);

	default_val = PLLX_MISC5_DEFAULT_VALUE;
	_pll_misc_chk_default(clk_base, pll->params, 5, default_val,
			PLLX_MISC5_WRITE_MASK);
}