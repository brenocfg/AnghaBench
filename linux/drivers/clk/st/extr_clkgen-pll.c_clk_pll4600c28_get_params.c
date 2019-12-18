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
struct stm_pll {unsigned long idf; unsigned long ndiv; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int clk_pll4600c28_get_params(unsigned long input, unsigned long output,
			  struct stm_pll *pll)
{

	unsigned long i, infin, n;
	unsigned long deviation = ~0;
	unsigned long new_freq, new_deviation;

	/* Output clock range: 19Mhz to 3000Mhz */
	if (output < 19000000 || output > 3000000000u)
		return -EINVAL;

	/* For better jitter, IDF should be smallest and NDIV must be maximum */
	for (i = 1; i <= 7 && deviation; i++) {
		/* INFIN checks */
		infin = input / i;
		if (infin < 4000000 || infin > 50000000)
			continue;	/* Invalid case */

		n = output / (infin * 2);
		if (n < 8 || n > 246)
			continue;	/* Invalid case */
		if (n < 246)
			n++;	/* To work around 'y' when n=x.y */

		for (; n >= 8 && deviation; n--) {
			new_freq = infin * 2 * n;
			if (new_freq < output)
				break;	/* Optimization: shorting loop */

			new_deviation = new_freq - output;
			if (!new_deviation || new_deviation < deviation) {
				pll->idf  = i;
				pll->ndiv = n;
				deviation = new_deviation;
			}
		}
	}

	if (deviation == ~0) /* No solution found */
		return -EINVAL;

	return 0;
}