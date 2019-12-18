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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_FSB_FREQ ; 
 int /*<<< orphan*/  MSR_IA32_EBL_CR_POWERON ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int pentium_core_get_frequency(void)
{
	u32 fsb = 0;
	u32 msr_lo, msr_tmp;
	int ret;

	rdmsr(MSR_FSB_FREQ, msr_lo, msr_tmp);
	/* see table B-2 of 25366920.pdf */
	switch (msr_lo & 0x07) {
	case 5:
		fsb = 100000;
		break;
	case 1:
		fsb = 133333;
		break;
	case 3:
		fsb = 166667;
		break;
	case 2:
		fsb = 200000;
		break;
	case 0:
		fsb = 266667;
		break;
	case 4:
		fsb = 333333;
		break;
	default:
		pr_err("PCORE - MSR_FSB_FREQ undefined value\n");
	}

	rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_tmp);
	pr_debug("PCORE - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x\n",
			msr_lo, msr_tmp);

	msr_tmp = (msr_lo >> 22) & 0x1f;
	pr_debug("bits 22-26 are 0x%x, speed is %u\n",
			msr_tmp, (msr_tmp * fsb));

	ret = (msr_tmp * fsb);
	return ret;
}