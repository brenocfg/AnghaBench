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
struct clk_sccg_pll_setup {int fout; int fout_request; int fout_error; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  memcpy (struct clk_sccg_pll_setup*,struct clk_sccg_pll_setup*,int) ; 

__attribute__((used)) static int clk_sccg_pll2_check_match(struct clk_sccg_pll_setup *setup,
					struct clk_sccg_pll_setup *temp_setup)
{
	int new_diff = temp_setup->fout - temp_setup->fout_request;
	int diff = temp_setup->fout_error;

	if (abs(diff) > abs(new_diff)) {
		temp_setup->fout_error = new_diff;
		memcpy(setup, temp_setup, sizeof(struct clk_sccg_pll_setup));

		if (temp_setup->fout_request == temp_setup->fout)
			return 0;
	}
	return -1;
}