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
struct stm_pll {int idf; unsigned long ndiv; } ;

/* Variables and functions */

__attribute__((used)) static int clk_pll4600c28_get_rate(unsigned long input, struct stm_pll *pll,
			unsigned long *rate)
{
	if (!pll->idf)
		pll->idf = 1;

	*rate = (input / pll->idf) * 2 * pll->ndiv;

	return 0;
}