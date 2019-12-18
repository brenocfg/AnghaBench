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
struct dpll_data {int last_rounded_n; long last_rounded_m; int last_rounded_lpmode; int /*<<< orphan*/  clk_ref; } ;

/* Variables and functions */
 long OMAP4_DPLL_LP_FINT_MAX ; 
 long OMAP4_DPLL_LP_FOUT_MAX ; 
 int clk_hw_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap4_dpll_lpmode_recalc(struct dpll_data *dd)
{
	long fint, fout;

	fint = clk_hw_get_rate(dd->clk_ref) / (dd->last_rounded_n + 1);
	fout = fint * dd->last_rounded_m;

	if ((fint < OMAP4_DPLL_LP_FINT_MAX) && (fout < OMAP4_DPLL_LP_FOUT_MAX))
		dd->last_rounded_lpmode = 1;
	else
		dd->last_rounded_lpmode = 0;
}