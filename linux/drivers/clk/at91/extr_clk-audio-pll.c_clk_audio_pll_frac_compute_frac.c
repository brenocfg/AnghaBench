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

/* Variables and functions */
 unsigned long long AT91_PMC_AUDIO_PLL_FRACR_MASK ; 
 unsigned long long AUDIO_PLL_DIV_FRAC ; 
 unsigned long long AUDIO_PLL_ND_MAX ; 
 unsigned long long DIV_ROUND_CLOSEST_ULL (unsigned long long,unsigned long) ; 
 int EINVAL ; 
 unsigned long long do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static int clk_audio_pll_frac_compute_frac(unsigned long rate,
					   unsigned long parent_rate,
					   unsigned long *nd,
					   unsigned long *fracr)
{
	unsigned long long tmp, rem;

	if (!rate)
		return -EINVAL;

	tmp = rate;
	rem = do_div(tmp, parent_rate);
	if (!tmp || tmp >= AUDIO_PLL_ND_MAX)
		return -EINVAL;

	*nd = tmp - 1;

	tmp = rem * AUDIO_PLL_DIV_FRAC;
	tmp = DIV_ROUND_CLOSEST_ULL(tmp, parent_rate);
	if (tmp > AT91_PMC_AUDIO_PLL_FRACR_MASK)
		return -EINVAL;

	/* we can cast here as we verified the bounds just above */
	*fracr = (unsigned long)tmp;

	return 0;
}