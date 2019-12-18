#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  pm_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_GLOBAL_WUEN_MASK ; 
 scalar_t__ PRM_INSTANCE_UNKNOWN ; 
 TYPE_1__ omap4_prcm_irq_setup ; 
 int /*<<< orphan*/  omap4_prm_rmw_inst_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ omap4_prmst_get_prm_dev_inst () ; 

__attribute__((used)) static void omap44xx_prm_enable_io_wakeup(void)
{
	s32 inst = omap4_prmst_get_prm_dev_inst();

	if (inst == PRM_INSTANCE_UNKNOWN)
		return;

	omap4_prm_rmw_inst_reg_bits(OMAP4430_GLOBAL_WUEN_MASK,
				    OMAP4430_GLOBAL_WUEN_MASK,
				    inst,
				    omap4_prcm_irq_setup.pm_ctrl);
}