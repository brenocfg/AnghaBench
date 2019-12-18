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
struct TYPE_4__ {TYPE_1__* ptr; } ;
struct clockdomain {scalar_t__ usecount; int /*<<< orphan*/  clktrctrl_mask; TYPE_2__ pwrdm; } ;
struct TYPE_3__ {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  clkdm_del_autodeps (struct clockdomain*) ; 
 int /*<<< orphan*/  omap3xxx_cm_clkdm_disable_hwsup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3xxx_clkdm_deny_idle(struct clockdomain *clkdm)
{
	omap3xxx_cm_clkdm_disable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					clkdm->clktrctrl_mask);

	if (clkdm->usecount > 0)
		clkdm_del_autodeps(clkdm);
}