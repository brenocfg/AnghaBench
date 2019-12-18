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
struct powerdomain {int context; int /*<<< orphan*/  pwrstctrl_offs; int /*<<< orphan*/  prcm_offs; int /*<<< orphan*/  prcm_partition; } ;

/* Variables and functions */
 int OMAP_POWERSTATEST_MASK ; 
 int omap4_prminst_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_prminst_write_inst_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_pwrdm_wait_transition (struct powerdomain*) ; 

__attribute__((used)) static void omap4_pwrdm_restore_context(struct powerdomain *pwrdm)
{
	int st, ctrl;

	st = omap4_prminst_read_inst_reg(pwrdm->prcm_partition,
					 pwrdm->prcm_offs,
					 pwrdm->pwrstctrl_offs);

	omap4_prminst_write_inst_reg(pwrdm->context,
				     pwrdm->prcm_partition,
				     pwrdm->prcm_offs,
				     pwrdm->pwrstctrl_offs);

	/* Make sure we only wait for a transition if there is one */
	st &= OMAP_POWERSTATEST_MASK;
	ctrl = OMAP_POWERSTATEST_MASK & pwrdm->context;

	if (st != ctrl)
		omap4_pwrdm_wait_transition(pwrdm);
}