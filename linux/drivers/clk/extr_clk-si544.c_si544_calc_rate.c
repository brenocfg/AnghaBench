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
struct clk_si544_muldiv {int delta_m; } ;
typedef  int s64 ;

/* Variables and functions */
 int DELTA_M_FRAC_DEN ; 
 int DELTA_M_FRAC_NUM ; 
 scalar_t__ DELTA_M_MAX ; 
 int div64_s64 (int,int) ; 
 unsigned long si544_calc_center_rate (struct clk_si544_muldiv const*) ; 

__attribute__((used)) static unsigned long si544_calc_rate(const struct clk_si544_muldiv *settings)
{
	unsigned long rate = si544_calc_center_rate(settings);
	s64 delta = (s64)rate * (DELTA_M_FRAC_NUM * settings->delta_m);

	/*
	 * The clock adjustment is much smaller than 1 Hz, round to the
	 * nearest multiple. Apparently div64_s64 rounds towards zero, hence
	 * check the sign and adjust into the proper direction.
	 */
	if (settings->delta_m < 0)
		delta -= ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN) / 2;
	else
		delta += ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN) / 2;
	delta = div64_s64(delta, ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN));

	return rate + delta;
}