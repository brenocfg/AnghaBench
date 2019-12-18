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
typedef  unsigned long u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct clk_si544_muldiv {unsigned long ls_div_bits; int hs_div; int fb_div_int; int fb_div_frac; scalar_t__ delta_m; } ;

/* Variables and functions */
 int FVCO_MIN ; 
 int FXO ; 
 int HS_DIV_MAX ; 
 int HS_DIV_MAX_ODD ; 
 unsigned long MIN_HSDIV_FREQ ; 
 int do_div (int,int) ; 

__attribute__((used)) static int si544_calc_muldiv(struct clk_si544_muldiv *settings,
	unsigned long frequency)
{
	u64 vco;
	u32 ls_freq;
	u32 tmp;
	u8 res;

	/* Determine the minimum value of LS_DIV and resulting target freq. */
	ls_freq = frequency;
	settings->ls_div_bits = 0;

	if (frequency >= MIN_HSDIV_FREQ) {
		settings->ls_div_bits = 0;
	} else {
		res = 1;
		tmp = 2 * HS_DIV_MAX;
		while (tmp <= (HS_DIV_MAX * 32)) {
			if (((u64)frequency * tmp) >= FVCO_MIN)
				break;
			++res;
			tmp <<= 1;
		}
		settings->ls_div_bits = res;
		ls_freq = frequency << res;
	}

	/* Determine minimum HS_DIV by rounding up */
	vco = FVCO_MIN + ls_freq - 1;
	do_div(vco, ls_freq);
	settings->hs_div = vco;

	/* round up to even number when required */
	if ((settings->hs_div & 1) &&
	    (settings->hs_div > HS_DIV_MAX_ODD || settings->ls_div_bits))
		++settings->hs_div;

	/* Calculate VCO frequency (in 10..12GHz range) */
	vco = (u64)ls_freq * settings->hs_div;

	/* Calculate the integer part of the feedback divider */
	tmp = do_div(vco, FXO);
	settings->fb_div_int = vco;

	/* And the fractional bits using the remainder */
	vco = (u64)tmp << 32;
	vco += FXO / 2; /* Round to nearest multiple */
	do_div(vco, FXO);
	settings->fb_div_frac = vco;

	/* Reset the frequency adjustment */
	settings->delta_m = 0;

	return 0;
}