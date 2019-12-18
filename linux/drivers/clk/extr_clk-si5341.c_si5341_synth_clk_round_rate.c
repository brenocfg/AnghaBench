#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct clk_si5341_synth {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long freq_vco; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI5341_SYNTH_N_MAX ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_MIN ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 struct clk_si5341_synth* to_clk_si5341_synth (struct clk_hw*) ; 

__attribute__((used)) static long si5341_synth_clk_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	struct clk_si5341_synth *synth = to_clk_si5341_synth(hw);
	u64 f;

	/* The synthesizer accuracy is such that anything in range will work */
	f = synth->data->freq_vco;
	do_div(f, SI5341_SYNTH_N_MAX);
	if (rate < f)
		return f;

	f = synth->data->freq_vco;
	do_div(f, SI5341_SYNTH_N_MIN);
	if (rate > f)
		return f;

	return rate;
}