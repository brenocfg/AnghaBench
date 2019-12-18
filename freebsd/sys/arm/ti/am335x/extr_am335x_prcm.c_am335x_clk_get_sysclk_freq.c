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
struct ti_clock_dev {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SCM_CTRL_STATUS ; 
 scalar_t__ ti_scm_reg_read_4 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
am335x_clk_get_sysclk_freq(struct ti_clock_dev *clkdev, unsigned int *freq)
{
	uint32_t ctrl_status;

	/* Read the input clock freq from the control module. */
	if (ti_scm_reg_read_4(SCM_CTRL_STATUS, &ctrl_status))
		return (ENXIO);

	switch ((ctrl_status>>22) & 0x3) {
	case 0x0:
		/* 19.2Mhz */
		*freq = 19200000;
		break;
	case 0x1:
		/* 24Mhz */
		*freq = 24000000;
		break;
	case 0x2:
		/* 25Mhz */
		*freq = 25000000;
		break;
	case 0x3:
		/* 26Mhz */
		*freq = 26000000;
		break;
	}

	return (0);
}