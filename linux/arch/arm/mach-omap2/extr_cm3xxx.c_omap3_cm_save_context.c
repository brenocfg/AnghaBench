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
struct TYPE_2__ {void* cm_clkout_ctrl; void* usbhost_cm_sleepdep; void* per_cm_sleepdep; void* cam_cm_sleepdep; void* dss_cm_sleepdep; void* sgx_cm_sleepdep; void* usbhost_cm_autoidle; void* per_cm_autoidle; void* cam_cm_autoidle; void* dss_cm_autoidle; void* wkup_cm_autoidle; void* core_cm_autoidle3; void* core_cm_autoidle2; void* core_cm_autoidle1; void* usbhost_cm_clkstctrl; void* neon_cm_clkstctrl; void* per_cm_clkstctrl; void* cam_cm_clkstctrl; void* dss_cm_clkstctrl; void* sgx_cm_clkstctrl; void* core_cm_clkstctrl; void* mpu_cm_clkstctrl; void* iva2_cm_clkstctrl; void* mpu_cm_autoidle2; void* iva2_cm_autoidle2; void* usbhost_cm_iclken; void* per_cm_iclken; void* cam_cm_iclken; void* dss_cm_iclken; void* wkup_cm_iclken; void* sgx_cm_iclken; void* core_cm_iclken3; void* core_cm_iclken2; void* core_cm_iclken1; void* usbhost_cm_fclken; void* per_cm_fclken; void* cam_cm_fclken; void* dss_cm_fclken; void* wkup_cm_fclken; void* sgx_cm_fclken; void* core_cm_fclken3; void* core_cm_fclken1; void* iva2_cm_clken_pll; void* iva2_cm_fclken; void* cm_polctrl; void* pll_cm_clken2; void* pll_cm_clksel5; void* pll_cm_clksel4; void* pll_cm_autoidle2; void* pll_cm_autoidle; void* emu_cm_clkstctrl; void* emu_cm_clksel; void* per_cm_clksel; void* cam_cm_clksel; void* dss_cm_clksel; void* sgx_cm_clksel; void* cm_sysconfig; void* iva2_cm_clksel2; void* iva2_cm_clksel1; } ;

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
 void* omap2_cm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3_cm_save_context(void)
{
	cm_context.iva2_cm_clksel1 =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, CM_CLKSEL1);
	cm_context.iva2_cm_clksel2 =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, CM_CLKSEL2);
	cm_context.cm_sysconfig =
		omap2_cm_read_mod_reg(OCP_MOD, OMAP3430_CM_SYSCONFIG);
	cm_context.sgx_cm_clksel =
		omap2_cm_read_mod_reg(OMAP3430ES2_SGX_MOD, CM_CLKSEL);
	cm_context.dss_cm_clksel =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, CM_CLKSEL);
	cm_context.cam_cm_clksel =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, CM_CLKSEL);
	cm_context.per_cm_clksel =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, CM_CLKSEL);
	cm_context.emu_cm_clksel =
		omap2_cm_read_mod_reg(OMAP3430_EMU_MOD, CM_CLKSEL1);
	cm_context.emu_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_EMU_MOD, OMAP2_CM_CLKSTCTRL);
	/*
	 * As per erratum i671, ROM code does not respect the PER DPLL
	 * programming scheme if CM_AUTOIDLE_PLL.AUTO_PERIPH_DPLL == 1.
	 * In this case, even though this register has been saved in
	 * scratchpad contents, we need to restore AUTO_PERIPH_DPLL
	 * by ourselves. So, we need to save it anyway.
	 */
	cm_context.pll_cm_autoidle =
		omap2_cm_read_mod_reg(PLL_MOD, CM_AUTOIDLE);
	cm_context.pll_cm_autoidle2 =
		omap2_cm_read_mod_reg(PLL_MOD, CM_AUTOIDLE2);
	cm_context.pll_cm_clksel4 =
		omap2_cm_read_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKSEL4);
	cm_context.pll_cm_clksel5 =
		omap2_cm_read_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKSEL5);
	cm_context.pll_cm_clken2 =
		omap2_cm_read_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKEN2);
	cm_context.cm_polctrl =
		omap2_cm_read_mod_reg(OCP_MOD, OMAP3430_CM_POLCTRL);
	cm_context.iva2_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, CM_FCLKEN);
	cm_context.iva2_cm_clken_pll =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, OMAP3430_CM_CLKEN_PLL);
	cm_context.core_cm_fclken1 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_FCLKEN1);
	cm_context.core_cm_fclken3 =
		omap2_cm_read_mod_reg(CORE_MOD, OMAP3430ES2_CM_FCLKEN3);
	cm_context.sgx_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430ES2_SGX_MOD, CM_FCLKEN);
	cm_context.wkup_cm_fclken =
		omap2_cm_read_mod_reg(WKUP_MOD, CM_FCLKEN);
	cm_context.dss_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, CM_FCLKEN);
	cm_context.cam_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, CM_FCLKEN);
	cm_context.per_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, CM_FCLKEN);
	cm_context.usbhost_cm_fclken =
		omap2_cm_read_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_FCLKEN);
	cm_context.core_cm_iclken1 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_ICLKEN1);
	cm_context.core_cm_iclken2 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_ICLKEN2);
	cm_context.core_cm_iclken3 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_ICLKEN3);
	cm_context.sgx_cm_iclken =
		omap2_cm_read_mod_reg(OMAP3430ES2_SGX_MOD, CM_ICLKEN);
	cm_context.wkup_cm_iclken =
		omap2_cm_read_mod_reg(WKUP_MOD, CM_ICLKEN);
	cm_context.dss_cm_iclken =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, CM_ICLKEN);
	cm_context.cam_cm_iclken =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, CM_ICLKEN);
	cm_context.per_cm_iclken =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, CM_ICLKEN);
	cm_context.usbhost_cm_iclken =
		omap2_cm_read_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_ICLKEN);
	cm_context.iva2_cm_autoidle2 =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, CM_AUTOIDLE2);
	cm_context.mpu_cm_autoidle2 =
		omap2_cm_read_mod_reg(MPU_MOD, CM_AUTOIDLE2);
	cm_context.iva2_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_IVA2_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.mpu_cm_clkstctrl =
		omap2_cm_read_mod_reg(MPU_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.core_cm_clkstctrl =
		omap2_cm_read_mod_reg(CORE_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.sgx_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430ES2_SGX_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.dss_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.cam_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.per_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.neon_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430_NEON_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.usbhost_cm_clkstctrl =
		omap2_cm_read_mod_reg(OMAP3430ES2_USBHOST_MOD,
				      OMAP2_CM_CLKSTCTRL);
	cm_context.core_cm_autoidle1 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_AUTOIDLE1);
	cm_context.core_cm_autoidle2 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_AUTOIDLE2);
	cm_context.core_cm_autoidle3 =
		omap2_cm_read_mod_reg(CORE_MOD, CM_AUTOIDLE3);
	cm_context.wkup_cm_autoidle =
		omap2_cm_read_mod_reg(WKUP_MOD, CM_AUTOIDLE);
	cm_context.dss_cm_autoidle =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, CM_AUTOIDLE);
	cm_context.cam_cm_autoidle =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, CM_AUTOIDLE);
	cm_context.per_cm_autoidle =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, CM_AUTOIDLE);
	cm_context.usbhost_cm_autoidle =
		omap2_cm_read_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_AUTOIDLE);
	cm_context.sgx_cm_sleepdep =
		omap2_cm_read_mod_reg(OMAP3430ES2_SGX_MOD,
				      OMAP3430_CM_SLEEPDEP);
	cm_context.dss_cm_sleepdep =
		omap2_cm_read_mod_reg(OMAP3430_DSS_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.cam_cm_sleepdep =
		omap2_cm_read_mod_reg(OMAP3430_CAM_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.per_cm_sleepdep =
		omap2_cm_read_mod_reg(OMAP3430_PER_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.usbhost_cm_sleepdep =
		omap2_cm_read_mod_reg(OMAP3430ES2_USBHOST_MOD,
				      OMAP3430_CM_SLEEPDEP);
	cm_context.cm_clkout_ctrl =
		omap2_cm_read_mod_reg(OMAP3430_CCR_MOD,
				      OMAP3_CM_CLKOUT_CTRL_OFFSET);
}