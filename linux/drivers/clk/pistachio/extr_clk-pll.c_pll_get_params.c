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
struct pistachio_pll_rate_table {unsigned long fref; unsigned long fout; } ;
struct pistachio_clk_pll {unsigned int nr_rates; struct pistachio_pll_rate_table* rates; } ;

/* Variables and functions */

__attribute__((used)) static struct pistachio_pll_rate_table *
pll_get_params(struct pistachio_clk_pll *pll, unsigned long fref,
	       unsigned long fout)
{
	unsigned int i;

	for (i = 0; i < pll->nr_rates; i++) {
		if (pll->rates[i].fref == fref && pll->rates[i].fout == fout)
			return &pll->rates[i];
	}

	return NULL;
}