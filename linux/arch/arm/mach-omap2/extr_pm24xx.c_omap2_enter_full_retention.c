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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  OCP_MOD ; 
 int /*<<< orphan*/  OMAP24XX_PM_WKST2 ; 
 int OMAP24XX_USBSTANDBYCTRL ; 
 int /*<<< orphan*/  OMAP2_CONTROL_DEVCONF0 ; 
 int /*<<< orphan*/  OMAP2_PRCM_IRQSTATUS_MPU_OFFSET ; 
 int /*<<< orphan*/  OMAP_SDRC_REGADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_WKST ; 
 int /*<<< orphan*/  PM_WKST1 ; 
 int /*<<< orphan*/  PWRDM_POWER_ON ; 
 int /*<<< orphan*/  PWRDM_POWER_RET ; 
 int /*<<< orphan*/  SDRC_DLLA_CTRL ; 
 int /*<<< orphan*/  SDRC_POWER ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_pwrdm ; 
 int /*<<< orphan*/  cpu_cluster_pm_enter () ; 
 int /*<<< orphan*/  cpu_cluster_pm_exit () ; 
 int /*<<< orphan*/  mpu_pwrdm ; 
 int /*<<< orphan*/  omap2_sram_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ omap_irq_pending () ; 
 int /*<<< orphan*/  omap_prm_clear_mod_irqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osc_ck ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdrc_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2_enter_full_retention(void)
{
	u32 l;

	/* There is 1 reference hold for all children of the oscillator
	 * clock, the following will remove it. If no one else uses the
	 * oscillator itself it will be disabled if/when we enter retention
	 * mode.
	 */
	clk_disable(osc_ck);

	/* Clear old wake-up events */
	/* REVISIT: These write to reserved bits? */
	omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
	omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);
	omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, ~0);

	pwrdm_set_next_pwrst(core_pwrdm, PWRDM_POWER_RET);
	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_RET);

	/* Workaround to kill USB */
	l = omap_ctrl_readl(OMAP2_CONTROL_DEVCONF0) | OMAP24XX_USBSTANDBYCTRL;
	omap_ctrl_writel(l, OMAP2_CONTROL_DEVCONF0);

	cpu_cluster_pm_enter();

	/* One last check for pending IRQs to avoid extra latency due
	 * to sleeping unnecessarily. */
	if (omap_irq_pending())
		goto no_sleep;

	/* Jump to SRAM suspend code */
	omap2_sram_suspend(sdrc_read_reg(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_POWER));

no_sleep:
	cpu_cluster_pm_exit();

	clk_enable(osc_ck);

	/* clear CORE wake-up events */
	omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
	omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);

	/* wakeup domain events - bit 1: GPT1, bit5 GPIO */
	omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, 0x4 | 0x1);

	/* MPU domain wake events */
	omap_prm_clear_mod_irqs(OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET, 0x1);

	omap_prm_clear_mod_irqs(OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET, 0x20);

	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
	pwrdm_set_next_pwrst(core_pwrdm, PWRDM_POWER_ON);

	return 0;
}