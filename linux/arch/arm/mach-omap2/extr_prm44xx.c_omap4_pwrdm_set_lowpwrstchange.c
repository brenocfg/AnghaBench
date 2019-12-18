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
struct powerdomain {int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_LOWPOWERSTATECHANGE_MASK ; 
 int OMAP4430_LOWPOWERSTATECHANGE_SHIFT ; 
 int /*<<< orphan*/  OMAP4_PM_PWSTCTRL ; 
 int /*<<< orphan*/  omap4_prminst_rmw_inst_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap4_pwrdm_set_lowpwrstchange(struct powerdomain *pwrdm)
{
	omap4_prminst_rmw_inst_reg_bits(OMAP4430_LOWPOWERSTATECHANGE_MASK,
					(1 << OMAP4430_LOWPOWERSTATECHANGE_SHIFT),
					pwrdm->prcm_partition,
					pwrdm->prcm_offs, OMAP4_PM_PWSTCTRL);
	return 0;
}