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

__attribute__((used)) static int ap806_get_sar_clocks(unsigned int freq_mode,
				unsigned int *cpuclk_freq,
				unsigned int *dclk_freq)
{
	switch (freq_mode) {
	case 0x0:
		*cpuclk_freq = 2000;
		*dclk_freq = 600;
		break;
	case 0x1:
		*cpuclk_freq = 2000;
		*dclk_freq = 525;
		break;
	case 0x6:
		*cpuclk_freq = 1800;
		*dclk_freq = 600;
		break;
	case 0x7:
		*cpuclk_freq = 1800;
		*dclk_freq = 525;
		break;
	case 0x4:
		*cpuclk_freq = 1600;
		*dclk_freq = 400;
		break;
	case 0xB:
		*cpuclk_freq = 1600;
		*dclk_freq = 450;
		break;
	case 0xD:
		*cpuclk_freq = 1600;
		*dclk_freq = 525;
		break;
	case 0x1a:
		*cpuclk_freq = 1400;
		*dclk_freq = 400;
		break;
	case 0x14:
		*cpuclk_freq = 1300;
		*dclk_freq = 400;
		break;
	case 0x17:
		*cpuclk_freq = 1300;
		*dclk_freq = 325;
		break;
	case 0x19:
		*cpuclk_freq = 1200;
		*dclk_freq = 400;
		break;
	case 0x13:
		*cpuclk_freq = 1000;
		*dclk_freq = 325;
		break;
	case 0x1d:
		*cpuclk_freq = 1000;
		*dclk_freq = 400;
		break;
	case 0x1c:
		*cpuclk_freq = 800;
		*dclk_freq = 400;
		break;
	case 0x1b:
		*cpuclk_freq = 600;
		*dclk_freq = 400;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}