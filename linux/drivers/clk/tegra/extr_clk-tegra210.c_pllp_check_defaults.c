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
 int PLLP_MISC0_DEFAULT_VALUE ; 
 int PLLP_MISC0_IDDQ ; 
 int PLLP_MISC0_LOCK_ENABLE ; 
 int PLLP_MISC0_LOCK_OVERRIDE ; 
 int PLLP_MISC0_WRITE_MASK ; 
 int PLLP_MISC1_DEFAULT_VALUE ; 
 int PLLP_MISC1_HSIO_EN ; 
 int PLLP_MISC1_WRITE_MASK ; 
 int PLLP_MISC1_XUSB_EN ; 
 int /*<<< orphan*/  _pll_misc_chk_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  clk_base ; 

__attribute__((used)) static void pllp_check_defaults(struct tegra_clk_pll *pll, bool enabled)
{
	u32 val, mask;

	/* Ignore lock enable (will be set), make sure not in IDDQ if enabled */
	val = PLLP_MISC0_DEFAULT_VALUE & (~PLLP_MISC0_IDDQ);
	mask = PLLP_MISC0_LOCK_ENABLE | PLLP_MISC0_LOCK_OVERRIDE;
	if (!enabled)
		mask |= PLLP_MISC0_IDDQ;
	_pll_misc_chk_default(clk_base, pll->params, 0, val,
			~mask & PLLP_MISC0_WRITE_MASK);

	/* Ignore branch controls */
	val = PLLP_MISC1_DEFAULT_VALUE;
	mask = PLLP_MISC1_HSIO_EN | PLLP_MISC1_XUSB_EN;
	_pll_misc_chk_default(clk_base, pll->params, 1, val,
			~mask & PLLP_MISC1_WRITE_MASK);
}