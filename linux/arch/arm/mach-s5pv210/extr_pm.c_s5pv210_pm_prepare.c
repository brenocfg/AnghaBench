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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int S5P_CFG_WFI_CLEAN ; 
 unsigned int S5P_CFG_WFI_SLEEP ; 
 int /*<<< orphan*/  S5P_INFORM0 ; 
 int /*<<< orphan*/  S5P_OTHERS ; 
 unsigned int S5P_OTHER_SYSC_INTOFF ; 
 int /*<<< orphan*/  S5P_PWR_CFG ; 
 int /*<<< orphan*/  S5P_SLEEP_CFG ; 
 unsigned int S5P_SLEEP_CFG_OSC_EN ; 
 unsigned int S5P_SLEEP_CFG_USBOSC_EN ; 
 int /*<<< orphan*/  S5P_WAKEUP_MASK ; 
 unsigned int __pa_symbol (int /*<<< orphan*/ ) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_pm_do_save (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pv210_core_save ; 
 int /*<<< orphan*/  s5pv210_cpu_resume ; 
 unsigned int s5pv210_irqwake_intmask ; 

__attribute__((used)) static void s5pv210_pm_prepare(void)
{
	unsigned int tmp;

	/*
	 * Set wake-up mask registers
	 * S5P_EINT_WAKEUP_MASK is set by pinctrl driver in late suspend.
	 */
	__raw_writel(s5pv210_irqwake_intmask, S5P_WAKEUP_MASK);

	/* ensure at least INFORM0 has the resume address */
	__raw_writel(__pa_symbol(s5pv210_cpu_resume), S5P_INFORM0);

	tmp = __raw_readl(S5P_SLEEP_CFG);
	tmp &= ~(S5P_SLEEP_CFG_OSC_EN | S5P_SLEEP_CFG_USBOSC_EN);
	__raw_writel(tmp, S5P_SLEEP_CFG);

	/* WFI for SLEEP mode configuration by SYSCON */
	tmp = __raw_readl(S5P_PWR_CFG);
	tmp &= S5P_CFG_WFI_CLEAN;
	tmp |= S5P_CFG_WFI_SLEEP;
	__raw_writel(tmp, S5P_PWR_CFG);

	/* SYSCON interrupt handling disable */
	tmp = __raw_readl(S5P_OTHERS);
	tmp |= S5P_OTHER_SYSC_INTOFF;
	__raw_writel(tmp, S5P_OTHERS);

	s3c_pm_do_save(s5pv210_core_save, ARRAY_SIZE(s5pv210_core_save));
}