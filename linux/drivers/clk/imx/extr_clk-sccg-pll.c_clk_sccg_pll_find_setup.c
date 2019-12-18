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
typedef  void* uint64_t ;
struct clk_sccg_pll_setup {int bypass; void* fout; void* fout_request; int /*<<< orphan*/  fout_error; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_BYPASS1 130 
#define  PLL_BYPASS2 129 
#define  PLL_BYPASS_NONE 128 
 int /*<<< orphan*/  PLL_OUT_MAX_FREQ ; 
 int clk_sccg_pll1_find_setup (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*,void*) ; 
 int clk_sccg_pll2_find_setup (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*,void*) ; 
 int /*<<< orphan*/  memset (struct clk_sccg_pll_setup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int clk_sccg_pll_find_setup(struct clk_sccg_pll_setup *setup,
					uint64_t prate,
					uint64_t rate, int try_bypass)
{
	struct clk_sccg_pll_setup temp_setup;
	int ret = -EINVAL;

	memset(&temp_setup, 0, sizeof(struct clk_sccg_pll_setup));
	memset(setup, 0, sizeof(struct clk_sccg_pll_setup));

	temp_setup.fout_error = PLL_OUT_MAX_FREQ;
	temp_setup.fout_request = rate;

	switch (try_bypass) {

	case PLL_BYPASS2:
		if (prate == rate) {
			setup->bypass = PLL_BYPASS2;
			setup->fout = rate;
			ret = 0;
		}
		break;

	case PLL_BYPASS1:
		ret = clk_sccg_pll2_find_setup(setup, &temp_setup, prate);
		break;

	case PLL_BYPASS_NONE:
		ret = clk_sccg_pll1_find_setup(setup, &temp_setup, prate);
		break;
	}

	return ret;
}