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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int nr_regs; scalar_t__ mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_PRM_OCP_SOCKET_INST ; 
 scalar_t__ OMAP4_REVISION_PRM_OFFSET ; 
 TYPE_1__ omap4_prcm_irq_setup ; 
 int /*<<< orphan*/  omap4_prm_read_inst_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  omap4_prm_write_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void omap44xx_prm_save_and_clear_irqen(u32 *saved_mask)
{
	int i;
	u16 reg;

	for (i = 0; i < omap4_prcm_irq_setup.nr_regs; i++) {
		reg = omap4_prcm_irq_setup.mask + i * 4;

		saved_mask[i] =
			omap4_prm_read_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
						reg);
		omap4_prm_write_inst_reg(0, OMAP4430_PRM_OCP_SOCKET_INST, reg);
	}

	/* OCP barrier */
	omap4_prm_read_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
				OMAP4_REVISION_PRM_OFFSET);
}