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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct fman_fpm_regs {int /*<<< orphan*/  fmfp_tsc1; int /*<<< orphan*/  fmfp_tsc2; } ;

/* Variables and functions */
 int FPM_TS_CTL_EN ; 
 int FPM_TS_INT_SHIFT ; 
 scalar_t__ do_div (int,int) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_enable_time_stamp(struct fman_fpm_regs *fpm_rg,
				uint8_t count1ubit,
				uint16_t fm_clk_freq)
{
	uint32_t tmp;
	uint64_t frac;
	uint32_t intgr;
	uint32_t ts_freq = (uint32_t)(1 << count1ubit); /* in Mhz */

	/* configure timestamp so that bit 8 will count 1 microsecond
	 * Find effective count rate at TIMESTAMP least significant bits:
	 * Effective_Count_Rate = 1MHz x 2^8 = 256MHz
	 * Find frequency ratio between effective count rate and the clock:
	 * Effective_Count_Rate / CLK e.g. for 600 MHz clock:
	 * 256/600 = 0.4266666... */

	intgr = ts_freq / fm_clk_freq;
	/* we multiply by 2^16 to keep the fraction of the division
	 * we do not div back, since we write this value as a fraction
	 * see spec */

	frac = ((uint64_t)ts_freq << 16) - ((uint64_t)intgr << 16) * fm_clk_freq;
	/* we check remainder of the division in order to round up if not int */
	if (do_div(frac, fm_clk_freq))
		frac++;

	tmp = (intgr << FPM_TS_INT_SHIFT) | (uint16_t)frac;
	iowrite32be(tmp, &fpm_rg->fmfp_tsc2);

	/* enable timestamp with original clock */
	iowrite32be(FPM_TS_CTL_EN, &fpm_rg->fmfp_tsc1);
}