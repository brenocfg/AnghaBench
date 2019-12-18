#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct sam9x60_pll {unsigned long div; unsigned long mul; unsigned long frac; struct clk_pll_characteristics* characteristics; } ;
struct clk_pll_characteristics {TYPE_1__* output; int /*<<< orphan*/  upll; } ;
struct TYPE_2__ {unsigned long min; unsigned long max; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST_ULL (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long ERANGE ; 
 unsigned long PLL_DIV_MAX ; 
 unsigned long PLL_MUL_MAX ; 
 unsigned long ULONG_MAX ; 
 unsigned long UPLL_DIV ; 
 unsigned long mult_frac (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static long sam9x60_pll_get_best_div_mul(struct sam9x60_pll *pll,
					 unsigned long rate,
					 unsigned long parent_rate,
					 bool update)
{
	const struct clk_pll_characteristics *characteristics =
							pll->characteristics;
	unsigned long bestremainder = ULONG_MAX;
	unsigned long maxdiv, mindiv, tmpdiv;
	long bestrate = -ERANGE;
	unsigned long bestdiv = 0;
	unsigned long bestmul = 0;
	unsigned long bestfrac = 0;

	if (rate < characteristics->output[0].min ||
	    rate > characteristics->output[0].max)
		return -ERANGE;

	if (!pll->characteristics->upll) {
		mindiv = parent_rate / rate;
		if (mindiv < 2)
			mindiv = 2;

		maxdiv = DIV_ROUND_UP(parent_rate * PLL_MUL_MAX, rate);
		if (maxdiv > PLL_DIV_MAX)
			maxdiv = PLL_DIV_MAX;
	} else {
		mindiv = maxdiv = UPLL_DIV;
	}

	for (tmpdiv = mindiv; tmpdiv <= maxdiv; tmpdiv++) {
		unsigned long remainder;
		unsigned long tmprate;
		unsigned long tmpmul;
		unsigned long tmpfrac = 0;

		/*
		 * Calculate the multiplier associated with the current
		 * divider that provide the closest rate to the requested one.
		 */
		tmpmul = mult_frac(rate, tmpdiv, parent_rate);
		tmprate = mult_frac(parent_rate, tmpmul, tmpdiv);
		remainder = rate - tmprate;

		if (remainder) {
			tmpfrac = DIV_ROUND_CLOSEST_ULL((u64)remainder * tmpdiv * (1 << 22),
							parent_rate);

			tmprate += DIV_ROUND_CLOSEST_ULL((u64)tmpfrac * parent_rate,
							 tmpdiv * (1 << 22));

			if (tmprate > rate)
				remainder = tmprate - rate;
			else
				remainder = rate - tmprate;
		}

		/*
		 * Compare the remainder with the best remainder found until
		 * now and elect a new best multiplier/divider pair if the
		 * current remainder is smaller than the best one.
		 */
		if (remainder < bestremainder) {
			bestremainder = remainder;
			bestdiv = tmpdiv;
			bestmul = tmpmul;
			bestrate = tmprate;
			bestfrac = tmpfrac;
		}

		/* We've found a perfect match!  */
		if (!remainder)
			break;
	}

	/* Check if bestrate is a valid output rate  */
	if (bestrate < characteristics->output[0].min &&
	    bestrate > characteristics->output[0].max)
		return -ERANGE;

	if (update) {
		pll->div = bestdiv - 1;
		pll->mul = bestmul - 1;
		pll->frac = bestfrac;
	}

	return bestrate;
}