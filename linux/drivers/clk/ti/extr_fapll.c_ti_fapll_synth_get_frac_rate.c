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
typedef  unsigned long u32 ;
struct fapll_synth {int /*<<< orphan*/  div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long SYNTH_MAX_DIV_M ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 unsigned long ti_fapll_synth_recalc_rate (struct clk_hw*,unsigned long) ; 
 struct fapll_synth* to_synth (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ti_fapll_synth_get_frac_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct fapll_synth *synth = to_synth(hw);
	unsigned long current_rate, frac_rate;
	u32 post_div_m;

	current_rate = ti_fapll_synth_recalc_rate(hw, parent_rate);
	post_div_m = readl_relaxed(synth->div) & SYNTH_MAX_DIV_M;
	frac_rate = current_rate * post_div_m;

	return frac_rate;
}