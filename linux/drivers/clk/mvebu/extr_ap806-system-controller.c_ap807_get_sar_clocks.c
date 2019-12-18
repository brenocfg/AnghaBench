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
 int EINVAL ; 

__attribute__((used)) static int ap807_get_sar_clocks(unsigned int freq_mode,
				unsigned int *cpuclk_freq,
				unsigned int *dclk_freq)
{
	switch (freq_mode) {
	case 0x0:
		*cpuclk_freq = 2000;
		*dclk_freq = 1200;
		break;
	case 0x6:
		*cpuclk_freq = 2200;
		*dclk_freq = 1200;
		break;
	case 0xD:
		*cpuclk_freq = 1600;
		*dclk_freq = 1200;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}