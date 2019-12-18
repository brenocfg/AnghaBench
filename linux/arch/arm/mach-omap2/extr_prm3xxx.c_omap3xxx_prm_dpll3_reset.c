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

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_RM_RSTCTRL ; 
 int /*<<< orphan*/  OMAP3430_GR_MOD ; 
 int /*<<< orphan*/  OMAP_RST_DPLL3_MASK ; 
 int /*<<< orphan*/  omap2_prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_prm_set_mod_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3xxx_prm_dpll3_reset(void)
{
	omap2_prm_set_mod_reg_bits(OMAP_RST_DPLL3_MASK, OMAP3430_GR_MOD,
				   OMAP2_RM_RSTCTRL);
	/* OCP barrier */
	omap2_prm_read_mod_reg(OMAP3430_GR_MOD, OMAP2_RM_RSTCTRL);
}