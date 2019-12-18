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
typedef  unsigned long u32 ;
struct clk_si514_muldiv {unsigned long ls_div_bits; int hs_div; unsigned long m_frac; unsigned long m_int; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int EINVAL ; 
 unsigned long FVCO_MIN ; 
 int FXO ; 
 unsigned long HS_DIV_MAX ; 
 unsigned long SI514_MAX_FREQ ; 
 unsigned long SI514_MIN_FREQ ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int si514_calc_muldiv(struct clk_si514_muldiv *settings,
	unsigned long frequency)
{
	u64 m;
	u32 ls_freq;
	u32 tmp;
	u8 res;

	if ((frequency < SI514_MIN_FREQ) || (frequency > SI514_MAX_FREQ))
		return -EINVAL;

	/* Determine the minimum value of LS_DIV and resulting target freq. */
	ls_freq = frequency;
	if (frequency >= (FVCO_MIN / HS_DIV_MAX))
		settings->ls_div_bits = 0;
	else {
		res = 1;
		tmp = 2 * HS_DIV_MAX;
		while (tmp <= (HS_DIV_MAX * 32)) {
			if ((frequency * tmp) >= FVCO_MIN)
				break;
			++res;
			tmp <<= 1;
		}
		settings->ls_div_bits = res;
		ls_freq = frequency << res;
	}

	/* Determine minimum HS_DIV, round up to even number */
	settings->hs_div = DIV_ROUND_UP(FVCO_MIN >> 1, ls_freq) << 1;

	/* M = LS_DIV x HS_DIV x frequency / F_XO (in fixed-point) */
	m = ((u64)(ls_freq * settings->hs_div) << 29) + (FXO / 2);
	do_div(m, FXO);
	settings->m_frac = (u32)m & (BIT(29) - 1);
	settings->m_int = (u32)(m >> 29);

	return 0;
}