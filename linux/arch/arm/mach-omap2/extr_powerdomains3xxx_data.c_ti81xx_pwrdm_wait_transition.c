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
typedef  scalar_t__ u32 ;
struct powerdomain {scalar_t__ prcm_offs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int OMAP_INTRANSITION_MASK ; 
 scalar_t__ PWRDM_TRANSITION_BAILOUT ; 
 scalar_t__ TI814X_PRM_GFX_MOD ; 
 int /*<<< orphan*/  TI81XX_PM_PWSTST ; 
 int /*<<< orphan*/  TI81XX_RM_RSTCTRL ; 
 int omap2_prm_read_mod_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ti81xx_pwrdm_wait_transition(struct powerdomain *pwrdm)
{
	u32 c = 0;

	while ((omap2_prm_read_mod_reg(pwrdm->prcm_offs,
		(pwrdm->prcm_offs == TI814X_PRM_GFX_MOD) ? TI81XX_RM_RSTCTRL :
				       TI81XX_PM_PWSTST) &
		OMAP_INTRANSITION_MASK) &&
		(c++ < PWRDM_TRANSITION_BAILOUT))
			udelay(1);

	if (c > PWRDM_TRANSITION_BAILOUT) {
		pr_err("powerdomain: %s timeout waiting for transition\n",
		       pwrdm->name);
		return -EAGAIN;
	}

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	return 0;
}