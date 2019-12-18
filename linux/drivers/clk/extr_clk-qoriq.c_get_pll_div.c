#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mux_hwclock {TYPE_2__* info; } ;
struct clockgen_pll_div {int dummy; } ;
struct clockgen {TYPE_1__* pll; } ;
struct TYPE_6__ {int flags; int pll; int div; } ;
struct TYPE_5__ {TYPE_3__* clksel; } ;
struct TYPE_4__ {struct clockgen_pll_div const* div; } ;

/* Variables and functions */
 int CLKSEL_VALID ; 

__attribute__((used)) static const struct clockgen_pll_div *get_pll_div(struct clockgen *cg,
						  struct mux_hwclock *hwc,
						  int idx)
{
	int pll, div;

	if (!(hwc->info->clksel[idx].flags & CLKSEL_VALID))
		return NULL;

	pll = hwc->info->clksel[idx].pll;
	div = hwc->info->clksel[idx].div;

	return &cg->pll[pll].div[div];
}