#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dpll_data {int freqsel_mask; int dcc_mask; scalar_t__ last_rounded_rate; scalar_t__ dcc_rate; int mult_mask; int div1_mask; int last_rounded_m; int last_rounded_n; int dco_mask; int sddiv_mask; int m4xen_mask; int lpmode_mask; int /*<<< orphan*/  control_reg; scalar_t__ last_rounded_lpmode; scalar_t__ last_rounded_m4xen; int /*<<< orphan*/  mult_div1_reg; } ;
struct clk_hw_omap {struct dpll_data* dpll_data; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int TI_CLK_DPLL_HAS_FREQSEL ; 
 int TI_CLK_ERRATA_I810 ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  _lookup_dco (struct clk_hw_omap*,int*,int,int) ; 
 int /*<<< orphan*/  _lookup_sddiv (struct clk_hw_omap*,int*,int,int) ; 
 int /*<<< orphan*/  _omap3_noncore_dpll_bypass (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  _omap3_noncore_dpll_lock (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  omap3_dpll_allow_idle (struct clk_hw_omap*) ; 
 int omap3_dpll_autoidle_read (struct clk_hw_omap*) ; 
 int /*<<< orphan*/  omap3_dpll_deny_idle (struct clk_hw_omap*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ *) ; 
 int stub5 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* ti_clk_get_features () ; 
 TYPE_1__* ti_clk_ll_ops ; 

__attribute__((used)) static int omap3_noncore_dpll_program(struct clk_hw_omap *clk, u16 freqsel)
{
	struct dpll_data *dd = clk->dpll_data;
	u8 dco, sd_div, ai = 0;
	u32 v;
	bool errata_i810;

	/* 3430 ES2 TRM: 4.7.6.9 DPLL Programming Sequence */
	_omap3_noncore_dpll_bypass(clk);

	/*
	 * Set jitter correction. Jitter correction applicable for OMAP343X
	 * only since freqsel field is no longer present on other devices.
	 */
	if (ti_clk_get_features()->flags & TI_CLK_DPLL_HAS_FREQSEL) {
		v = ti_clk_ll_ops->clk_readl(&dd->control_reg);
		v &= ~dd->freqsel_mask;
		v |= freqsel << __ffs(dd->freqsel_mask);
		ti_clk_ll_ops->clk_writel(v, &dd->control_reg);
	}

	/* Set DPLL multiplier, divider */
	v = ti_clk_ll_ops->clk_readl(&dd->mult_div1_reg);

	/* Handle Duty Cycle Correction */
	if (dd->dcc_mask) {
		if (dd->last_rounded_rate >= dd->dcc_rate)
			v |= dd->dcc_mask; /* Enable DCC */
		else
			v &= ~dd->dcc_mask; /* Disable DCC */
	}

	v &= ~(dd->mult_mask | dd->div1_mask);
	v |= dd->last_rounded_m << __ffs(dd->mult_mask);
	v |= (dd->last_rounded_n - 1) << __ffs(dd->div1_mask);

	/* Configure dco and sd_div for dplls that have these fields */
	if (dd->dco_mask) {
		_lookup_dco(clk, &dco, dd->last_rounded_m, dd->last_rounded_n);
		v &= ~(dd->dco_mask);
		v |= dco << __ffs(dd->dco_mask);
	}
	if (dd->sddiv_mask) {
		_lookup_sddiv(clk, &sd_div, dd->last_rounded_m,
			      dd->last_rounded_n);
		v &= ~(dd->sddiv_mask);
		v |= sd_div << __ffs(dd->sddiv_mask);
	}

	/*
	 * Errata i810 - DPLL controller can get stuck while transitioning
	 * to a power saving state. Software must ensure the DPLL can not
	 * transition to a low power state while changing M/N values.
	 * Easiest way to accomplish this is to prevent DPLL autoidle
	 * before doing the M/N re-program.
	 */
	errata_i810 = ti_clk_get_features()->flags & TI_CLK_ERRATA_I810;

	if (errata_i810) {
		ai = omap3_dpll_autoidle_read(clk);
		if (ai) {
			omap3_dpll_deny_idle(clk);

			/* OCP barrier */
			omap3_dpll_autoidle_read(clk);
		}
	}

	ti_clk_ll_ops->clk_writel(v, &dd->mult_div1_reg);

	/* Set 4X multiplier and low-power mode */
	if (dd->m4xen_mask || dd->lpmode_mask) {
		v = ti_clk_ll_ops->clk_readl(&dd->control_reg);

		if (dd->m4xen_mask) {
			if (dd->last_rounded_m4xen)
				v |= dd->m4xen_mask;
			else
				v &= ~dd->m4xen_mask;
		}

		if (dd->lpmode_mask) {
			if (dd->last_rounded_lpmode)
				v |= dd->lpmode_mask;
			else
				v &= ~dd->lpmode_mask;
		}

		ti_clk_ll_ops->clk_writel(v, &dd->control_reg);
	}

	/* We let the clock framework set the other output dividers later */

	/* REVISIT: Set ramp-up delay? */

	_omap3_noncore_dpll_lock(clk);

	if (errata_i810 && ai)
		omap3_dpll_allow_idle(clk);

	return 0;
}