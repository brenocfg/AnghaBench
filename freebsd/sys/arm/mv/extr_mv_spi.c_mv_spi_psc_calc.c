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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int get_tclk_armada38x () ; 

__attribute__((used)) static int
mv_spi_psc_calc(uint32_t clock, uint32_t *spr, uint32_t *sppr)
{
	uint32_t divider, tclk;

	tclk = get_tclk_armada38x();
	for (*spr = 2; *spr <= 15; (*spr)++) {
		for (*sppr = 0; *sppr <= 7; (*sppr)++) {
			divider = *spr * (1 << *sppr);
			if (tclk / divider <= clock)
				return (0);
		}
	}

	return (EINVAL);
}