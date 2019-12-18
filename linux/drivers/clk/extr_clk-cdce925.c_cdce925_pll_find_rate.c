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
typedef  unsigned long u16 ;

/* Variables and functions */
 unsigned long CDCE925_PLL_FREQUENCY_MAX ; 
 unsigned long CDCE925_PLL_FREQUENCY_MIN ; 
 unsigned long gcd (unsigned long,unsigned long) ; 

__attribute__((used)) static void cdce925_pll_find_rate(unsigned long rate,
		unsigned long parent_rate, u16 *n, u16 *m)
{
	unsigned long un;
	unsigned long um;
	unsigned long g;

	if (rate <= parent_rate) {
		/* Can always deliver parent_rate in bypass mode */
		rate = parent_rate;
		*n = 0;
		*m = 0;
	} else {
		/* In PLL mode, need to apply min/max range */
		if (rate < CDCE925_PLL_FREQUENCY_MIN)
			rate = CDCE925_PLL_FREQUENCY_MIN;
		else if (rate > CDCE925_PLL_FREQUENCY_MAX)
			rate = CDCE925_PLL_FREQUENCY_MAX;

		g = gcd(rate, parent_rate);
		um = parent_rate / g;
		un = rate / g;
		/* When outside hw range, reduce to fit (rounding errors) */
		while ((un > 4095) || (um > 511)) {
			un >>= 1;
			um >>= 1;
		}
		if (un == 0)
			un = 1;
		if (um == 0)
			um = 1;

		*n = un;
		*m = um;
	}
}