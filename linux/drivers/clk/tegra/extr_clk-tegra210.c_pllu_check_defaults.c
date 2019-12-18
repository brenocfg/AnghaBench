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
struct tegra_clk_pll_params {int dummy; } ;

/* Variables and functions */
 int PLLU_MISC0_DEFAULT_VALUE ; 
 int PLLU_MISC0_IDDQ ; 
 int PLLU_MISC0_LOCK_ENABLE ; 
 int PLLU_MISC0_WRITE_MASK ; 
 int PLLU_MISC1_DEFAULT_VALUE ; 
 int PLLU_MISC1_LOCK_OVERRIDE ; 
 int PLLU_MISC1_WRITE_MASK ; 
 int /*<<< orphan*/  _pll_misc_chk_default (int /*<<< orphan*/ ,struct tegra_clk_pll_params*,int,int,int) ; 
 int /*<<< orphan*/  clk_base ; 

__attribute__((used)) static void pllu_check_defaults(struct tegra_clk_pll_params *params,
				bool hw_control)
{
	u32 val, mask;

	/* Ignore lock enable (will be set) and IDDQ if under h/w control */
	val = PLLU_MISC0_DEFAULT_VALUE & (~PLLU_MISC0_IDDQ);
	mask = PLLU_MISC0_LOCK_ENABLE | (hw_control ? PLLU_MISC0_IDDQ : 0);
	_pll_misc_chk_default(clk_base, params, 0, val,
			~mask & PLLU_MISC0_WRITE_MASK);

	val = PLLU_MISC1_DEFAULT_VALUE;
	mask = PLLU_MISC1_LOCK_OVERRIDE;
	_pll_misc_chk_default(clk_base, params, 1, val,
			~mask & PLLU_MISC1_WRITE_MASK);
}