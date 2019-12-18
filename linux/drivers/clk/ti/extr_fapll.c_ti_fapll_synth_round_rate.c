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
struct fapll_synth {int /*<<< orphan*/  freq; int /*<<< orphan*/  div; struct fapll_data* fd; } ;
struct fapll_data {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP_ULL (unsigned long,int) ; 
 long EINVAL ; 
 int SYNTH_MAX_DIV_M ; 
 int SYNTH_MAX_INT_DIV ; 
 unsigned long SYNTH_PHASE_K ; 
 scalar_t__ ti_fapll_clock_is_bypass (struct fapll_data*) ; 
 unsigned long ti_fapll_synth_get_frac_rate (struct clk_hw*,unsigned long) ; 
 struct fapll_synth* to_synth (struct clk_hw*) ; 

__attribute__((used)) static long ti_fapll_synth_round_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long *parent_rate)
{
	struct fapll_synth *synth = to_synth(hw);
	struct fapll_data *fd = synth->fd;
	unsigned long r;

	if (ti_fapll_clock_is_bypass(fd) || !synth->div || !rate)
		return -EINVAL;

	/* Only post divider m available with no fractional divider? */
	if (!synth->freq) {
		unsigned long frac_rate;
		u32 synth_post_div_m;

		frac_rate = ti_fapll_synth_get_frac_rate(hw, *parent_rate);
		synth_post_div_m = DIV_ROUND_UP(frac_rate, rate);
		r = DIV_ROUND_UP(frac_rate, synth_post_div_m);
		goto out;
	}

	r = *parent_rate * SYNTH_PHASE_K;
	if (rate > r)
		goto out;

	r = DIV_ROUND_UP_ULL(r, SYNTH_MAX_INT_DIV * SYNTH_MAX_DIV_M);
	if (rate < r)
		goto out;

	r = rate;
out:
	return r;
}