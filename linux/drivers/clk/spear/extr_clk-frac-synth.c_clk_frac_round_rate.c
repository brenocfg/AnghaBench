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
struct clk_hw {int dummy; } ;
struct clk_frac {int /*<<< orphan*/  rtbl_cnt; } ;

/* Variables and functions */
 long clk_round_rate_index (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  frac_calc_rate ; 
 struct clk_frac* to_clk_frac (struct clk_hw*) ; 

__attribute__((used)) static long clk_frac_round_rate(struct clk_hw *hw, unsigned long drate,
		unsigned long *prate)
{
	struct clk_frac *frac = to_clk_frac(hw);
	int unused;

	return clk_round_rate_index(hw, drate, *prate, frac_calc_rate,
			frac->rtbl_cnt, &unused);
}