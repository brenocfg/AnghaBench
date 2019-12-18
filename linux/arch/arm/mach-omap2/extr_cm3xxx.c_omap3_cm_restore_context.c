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
struct TYPE_2__ {int /*<<< orphan*/  cm_clkout_ctrl; int /*<<< orphan*/  usbhost_cm_sleepdep; int /*<<< orphan*/  per_cm_sleepdep; int /*<<< orphan*/  cam_cm_sleepdep; int /*<<< orphan*/  dss_cm_sleepdep; int /*<<< orphan*/  sgx_cm_sleepdep; int /*<<< orphan*/  usbhost_cm_autoidle; int /*<<< orphan*/  per_cm_autoidle; int /*<<< orphan*/  cam_cm_autoidle; int /*<<< orphan*/  dss_cm_autoidle; int /*<<< orphan*/  wkup_cm_autoidle; int /*<<< orphan*/  core_cm_autoidle3; int /*<<< orphan*/  core_cm_autoidle2; int /*<<< orphan*/  core_cm_autoidle1; int /*<<< orphan*/  usbhost_cm_clkstctrl; int /*<<< orphan*/  neon_cm_clkstctrl; int /*<<< orphan*/  per_cm_clkstctrl; int /*<<< orphan*/  cam_cm_clkstctrl; int /*<<< orphan*/  dss_cm_clkstctrl; int /*<<< orphan*/  sgx_cm_clkstctrl; int /*<<< orphan*/  core_cm_clkstctrl; int /*<<< orphan*/  mpu_cm_clkstctrl; int /*<<< orphan*/  iva2_cm_clkstctrl; int /*<<< orphan*/  mpu_cm_autoidle2; int /*<<< orphan*/  iva2_cm_autoidle2; int /*<<< orphan*/  usbhost_cm_iclken; int /*<<< orphan*/  per_cm_iclken; int /*<<< orphan*/  cam_cm_iclken; int /*<<< orphan*/  dss_cm_iclken; int /*<<< orphan*/  wkup_cm_iclken; int /*<<< orphan*/  sgx_cm_iclken; int /*<<< orphan*/  core_cm_iclken3; int /*<<< orphan*/  core_cm_iclken2; int /*<<< orphan*/  core_cm_iclken1; int /*<<< orphan*/  usbhost_cm_fclken; int /*<<< orphan*/  per_cm_fclken; int /*<<< orphan*/  cam_cm_fclken; int /*<<< orphan*/  dss_cm_fclken; int /*<<< orphan*/  wkup_cm_fclken; int /*<<< orphan*/  sgx_cm_fclken; int /*<<< orphan*/  core_cm_fclken3; int /*<<< orphan*/  core_cm_fclken1; int /*<<< orphan*/  iva2_cm_clken_pll; int /*<<< orphan*/  iva2_cm_fclken; int /*<<< orphan*/  cm_polctrl; int /*<<< orphan*/  pll_cm_clken2; int /*<<< orphan*/  pll_cm_clksel5; int /*<<< orphan*/  pll_cm_clksel4; int /*<<< orphan*/  pll_cm_autoidle2; int /*<<< orphan*/  pll_cm_autoidle; int /*<<< orphan*/  emu_cm_clkstctrl; int /*<<< orphan*/  emu_cm_clksel; int /*<<< orphan*/  per_cm_clksel; int /*<<< orphan*/  cam_cm_clksel; int /*<<< orphan*/  dss_cm_clksel; int /*<<< orphan*/  sgx_cm_clksel; int /*<<< orphan*/  cm_sysconfig; int /*<<< orphan*/  iva2_cm_clksel2; int /*<<< orphan*/  iva2_cm_clksel1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_AUTOIDLE ; 
 int /*<<< orphan*/  CM_AUTOIDLE1 ; 
 int /*<<< orphan*/  CM_AUTOIDLE2 ; 
 int /*<<< orphan*/  CM_AUTOIDLE3 ; 
 int /*<<< orphan*/  CM_CLKSEL ; 
 int /*<<< orphan*/  CM_CLKSEL1 ; 
 int /*<<< orphan*/  CM_CLKSEL2 ; 
 int /*<<< orphan*/  CM_FCLKEN ; 
 int /*<<< orphan*/  CM_FCLKEN1 ; 
 int /*<<< orphan*/  CM_ICLKEN ; 
 int /*<<< orphan*/  CM_ICLKEN1 ; 
 int /*<<< orphan*/  CM_ICLKEN2 ; 
 int /*<<< orphan*/  CM_ICLKEN3 ; 
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  MPU_MOD ; 
 int /*<<< orphan*/  OCP_MOD ; 
 int /*<<< orphan*/  OMAP2_CM_CLKSTCTRL ; 
 int /*<<< orphan*/  OMAP3430ES2_CM_CLKEN2 ; 
 int /*<<< orphan*/  OMAP3430ES2_CM_CLKSEL4 ; 
 int /*<<< orphan*/  OMAP3430ES2_CM_CLKSEL5 ; 
 int /*<<< orphan*/  OMAP3430ES2_CM_FCLKEN3 ; 
 int /*<<< orphan*/  OMAP3430ES2_SGX_MOD ; 
 int /*<<< orphan*/  OMAP3430ES2_USBHOST_MOD ; 
 int /*<<< orphan*/  OMAP3430_CAM_MOD ; 
 int /*<<< orphan*/  OMAP3430_CCR_MOD ; 
 int /*<<< orphan*/  OMAP3430_CM_CLKEN_PLL ; 
 int /*<<< orphan*/  OMAP3430_CM_POLCTRL ; 
 int /*<<< orphan*/  OMAP3430_CM_SLEEPDEP ; 
 int /*<<< orphan*/  OMAP3430_CM_SYSCONFIG ; 
 int /*<<< orphan*/  OMAP3430_DSS_MOD ; 
 int /*<<< orphan*/  OMAP3430_EMU_MOD ; 
 int /*<<< orphan*/  OMAP3430_IVA2_MOD ; 
 int /*<<< orphan*/  OMAP3430_NEON_MOD ; 
 int /*<<< orphan*/  OMAP3430_PER_MOD ; 
 int /*<<< orphan*/  OMAP3_CM_CLKOUT_CTRL_OFFSET ; 
 int /*<<< orphan*/  PLL_MOD ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 TYPE_1__ cm_context ; 
 int /*<<< orphan*/  omap2_cm_write_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3_cm_restore_context(void)
{
	omap2_cm_write_mod_reg(cm_context.iva2_cm_clksel1, OMAP3430_IVA2_MOD,
			       CM_CLKSEL1);
	omap2_cm_write_mod_reg(cm_context.iva2_cm_clksel2, OMAP3430_IVA2_MOD,
			       CM_CLKSEL2);
	omap2_cm_write_mod_reg(cm_context.cm_sysconfig, OCP_MOD,
			       OMAP3430_CM_SYSCONFIG);
	omap2_cm_write_mod_reg(cm_context.sgx_cm_clksel, OMAP3430ES2_SGX_MOD,
			       CM_CLKSEL);
	omap2_cm_write_mod_reg(cm_context.dss_cm_clksel, OMAP3430_DSS_MOD,
			       CM_CLKSEL);
	omap2_cm_write_mod_reg(cm_context.cam_cm_clksel, OMAP3430_CAM_MOD,
			       CM_CLKSEL);
	omap2_cm_write_mod_reg(cm_context.per_cm_clksel, OMAP3430_PER_MOD,
			       CM_CLKSEL);
	omap2_cm_write_mod_reg(cm_context.emu_cm_clksel, OMAP3430_EMU_MOD,
			       CM_CLKSEL1);
	omap2_cm_write_mod_reg(cm_context.emu_cm_clkstctrl, OMAP3430_EMU_MOD,
			       OMAP2_CM_CLKSTCTRL);
	/*
	 * As per erratum i671, ROM code does not respect the PER DPLL
	 * programming scheme if CM_AUTOIDLE_PLL.AUTO_PERIPH_DPLL == 1.
	 * In this case, we need to restore AUTO_PERIPH_DPLL by ourselves.
	 */
	omap2_cm_write_mod_reg(cm_context.pll_cm_autoidle, PLL_MOD,
			       CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.pll_cm_autoidle2, PLL_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_write_mod_reg(cm_context.pll_cm_clksel4, PLL_MOD,
			       OMAP3430ES2_CM_CLKSEL4);
	omap2_cm_write_mod_reg(cm_context.pll_cm_clksel5, PLL_MOD,
			       OMAP3430ES2_CM_CLKSEL5);
	omap2_cm_write_mod_reg(cm_context.pll_cm_clken2, PLL_MOD,
			       OMAP3430ES2_CM_CLKEN2);
	omap2_cm_write_mod_reg(cm_context.cm_polctrl, OCP_MOD,
			       OMAP3430_CM_POLCTRL);
	omap2_cm_write_mod_reg(cm_context.iva2_cm_fclken, OMAP3430_IVA2_MOD,
			       CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.iva2_cm_clken_pll, OMAP3430_IVA2_MOD,
			       OMAP3430_CM_CLKEN_PLL);
	omap2_cm_write_mod_reg(cm_context.core_cm_fclken1, CORE_MOD,
			       CM_FCLKEN1);
	omap2_cm_write_mod_reg(cm_context.core_cm_fclken3, CORE_MOD,
			       OMAP3430ES2_CM_FCLKEN3);
	omap2_cm_write_mod_reg(cm_context.sgx_cm_fclken, OMAP3430ES2_SGX_MOD,
			       CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.wkup_cm_fclken, WKUP_MOD, CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.dss_cm_fclken, OMAP3430_DSS_MOD,
			       CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.cam_cm_fclken, OMAP3430_CAM_MOD,
			       CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.per_cm_fclken, OMAP3430_PER_MOD,
			       CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.usbhost_cm_fclken,
			       OMAP3430ES2_USBHOST_MOD, CM_FCLKEN);
	omap2_cm_write_mod_reg(cm_context.core_cm_iclken1, CORE_MOD,
			       CM_ICLKEN1);
	omap2_cm_write_mod_reg(cm_context.core_cm_iclken2, CORE_MOD,
			       CM_ICLKEN2);
	omap2_cm_write_mod_reg(cm_context.core_cm_iclken3, CORE_MOD,
			       CM_ICLKEN3);
	omap2_cm_write_mod_reg(cm_context.sgx_cm_iclken, OMAP3430ES2_SGX_MOD,
			       CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.wkup_cm_iclken, WKUP_MOD, CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.dss_cm_iclken, OMAP3430_DSS_MOD,
			       CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.cam_cm_iclken, OMAP3430_CAM_MOD,
			       CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.per_cm_iclken, OMAP3430_PER_MOD,
			       CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.usbhost_cm_iclken,
			       OMAP3430ES2_USBHOST_MOD, CM_ICLKEN);
	omap2_cm_write_mod_reg(cm_context.iva2_cm_autoidle2, OMAP3430_IVA2_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_write_mod_reg(cm_context.mpu_cm_autoidle2, MPU_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_write_mod_reg(cm_context.iva2_cm_clkstctrl, OMAP3430_IVA2_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.mpu_cm_clkstctrl, MPU_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.core_cm_clkstctrl, CORE_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.sgx_cm_clkstctrl, OMAP3430ES2_SGX_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.dss_cm_clkstctrl, OMAP3430_DSS_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.cam_cm_clkstctrl, OMAP3430_CAM_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.per_cm_clkstctrl, OMAP3430_PER_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.neon_cm_clkstctrl, OMAP3430_NEON_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.usbhost_cm_clkstctrl,
			       OMAP3430ES2_USBHOST_MOD, OMAP2_CM_CLKSTCTRL);
	omap2_cm_write_mod_reg(cm_context.core_cm_autoidle1, CORE_MOD,
			       CM_AUTOIDLE1);
	omap2_cm_write_mod_reg(cm_context.core_cm_autoidle2, CORE_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_write_mod_reg(cm_context.core_cm_autoidle3, CORE_MOD,
			       CM_AUTOIDLE3);
	omap2_cm_write_mod_reg(cm_context.wkup_cm_autoidle, WKUP_MOD,
			       CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.dss_cm_autoidle, OMAP3430_DSS_MOD,
			       CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.cam_cm_autoidle, OMAP3430_CAM_MOD,
			       CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.per_cm_autoidle, OMAP3430_PER_MOD,
			       CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.usbhost_cm_autoidle,
			       OMAP3430ES2_USBHOST_MOD, CM_AUTOIDLE);
	omap2_cm_write_mod_reg(cm_context.sgx_cm_sleepdep, OMAP3430ES2_SGX_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_write_mod_reg(cm_context.dss_cm_sleepdep, OMAP3430_DSS_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_write_mod_reg(cm_context.cam_cm_sleepdep, OMAP3430_CAM_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_write_mod_reg(cm_context.per_cm_sleepdep, OMAP3430_PER_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_write_mod_reg(cm_context.usbhost_cm_sleepdep,
			       OMAP3430ES2_USBHOST_MOD, OMAP3430_CM_SLEEPDEP);
	omap2_cm_write_mod_reg(cm_context.cm_clkout_ctrl, OMAP3430_CCR_MOD,
			       OMAP3_CM_CLKOUT_CTRL_OFFSET);
}