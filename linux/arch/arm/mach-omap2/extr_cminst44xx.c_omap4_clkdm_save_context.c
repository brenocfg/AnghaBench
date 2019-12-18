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
struct clockdomain {int /*<<< orphan*/  context; scalar_t__ clkdm_offs; int /*<<< orphan*/  cm_inst; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_MODULEMODE_MASK ; 
 scalar_t__ OMAP4_CM_CLKSTCTRL ; 
 int /*<<< orphan*/  omap4_cminst_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int omap4_clkdm_save_context(struct clockdomain *clkdm)
{
	clkdm->context = omap4_cminst_read_inst_reg(clkdm->prcm_partition,
						    clkdm->cm_inst,
						    clkdm->clkdm_offs +
						    OMAP4_CM_CLKSTCTRL);
	clkdm->context &= OMAP4430_MODULEMODE_MASK;
	return 0;
}