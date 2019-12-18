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
 int /*<<< orphan*/  AM33XX_CM_GFX_GFX_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_MPU_MPU_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_AES0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_DCAN0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_DCAN1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_ELM_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_EPWMSS0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_EPWMSS1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_EPWMSS2_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_GPIO1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_GPIO2_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_GPIO3_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_GPMC_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_L3_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_L3_INSTR_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_L4LS_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_MAILBOX0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_MCASP0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_MCASP1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_OCMCRAM_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_PRUSS_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_RNG_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_SHA0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_SPI0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_SPI1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_SPINLOCK_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER2_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER3_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER4_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER5_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER6_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TIMER7_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TPCC_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TPTC0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TPTC1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_PER_TPTC2_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_RTC_RTC_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_WKUP_L4WKUP_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_WKUP_SMARTREFLEX0_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_WKUP_SMARTREFLEX1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_WKUP_TIMER1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_CM_WKUP_WDT1_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  CLKCTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWMOD_OMAP4_ZERO_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  PRCM_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am33xx_aes0_hwmod ; 
 int /*<<< orphan*/  am33xx_dcan0_hwmod ; 
 int /*<<< orphan*/  am33xx_dcan1_hwmod ; 
 int /*<<< orphan*/  am33xx_elm_hwmod ; 
 int /*<<< orphan*/  am33xx_epwmss0_hwmod ; 
 int /*<<< orphan*/  am33xx_epwmss1_hwmod ; 
 int /*<<< orphan*/  am33xx_epwmss2_hwmod ; 
 int /*<<< orphan*/  am33xx_gfx_hwmod ; 
 int /*<<< orphan*/  am33xx_gpio1_hwmod ; 
 int /*<<< orphan*/  am33xx_gpio2_hwmod ; 
 int /*<<< orphan*/  am33xx_gpio3_hwmod ; 
 int /*<<< orphan*/  am33xx_gpmc_hwmod ; 
 int /*<<< orphan*/  am33xx_l3_instr_hwmod ; 
 int /*<<< orphan*/  am33xx_l3_main_hwmod ; 
 int /*<<< orphan*/  am33xx_l4_ls_hwmod ; 
 int /*<<< orphan*/  am33xx_l4_wkup_hwmod ; 
 int /*<<< orphan*/  am33xx_mailbox_hwmod ; 
 int /*<<< orphan*/  am33xx_mcasp0_hwmod ; 
 int /*<<< orphan*/  am33xx_mcasp1_hwmod ; 
 int /*<<< orphan*/  am33xx_mpu_hwmod ; 
 int /*<<< orphan*/  am33xx_ocmcram_hwmod ; 
 int /*<<< orphan*/  am33xx_pruss_hwmod ; 
 int /*<<< orphan*/  am33xx_rng_hwmod ; 
 int /*<<< orphan*/  am33xx_rtc_hwmod ; 
 int /*<<< orphan*/  am33xx_sha0_hwmod ; 
 int /*<<< orphan*/  am33xx_smartreflex0_hwmod ; 
 int /*<<< orphan*/  am33xx_smartreflex1_hwmod ; 
 int /*<<< orphan*/  am33xx_spi0_hwmod ; 
 int /*<<< orphan*/  am33xx_spi1_hwmod ; 
 int /*<<< orphan*/  am33xx_spinlock_hwmod ; 
 int /*<<< orphan*/  am33xx_timer1_hwmod ; 
 int /*<<< orphan*/  am33xx_timer2_hwmod ; 
 int /*<<< orphan*/  am33xx_timer3_hwmod ; 
 int /*<<< orphan*/  am33xx_timer4_hwmod ; 
 int /*<<< orphan*/  am33xx_timer5_hwmod ; 
 int /*<<< orphan*/  am33xx_timer6_hwmod ; 
 int /*<<< orphan*/  am33xx_timer7_hwmod ; 
 int /*<<< orphan*/  am33xx_tpcc_hwmod ; 
 int /*<<< orphan*/  am33xx_tptc0_hwmod ; 
 int /*<<< orphan*/  am33xx_tptc1_hwmod ; 
 int /*<<< orphan*/  am33xx_tptc2_hwmod ; 
 int /*<<< orphan*/  am33xx_wd_timer1_hwmod ; 

__attribute__((used)) static void omap_hwmod_am33xx_clkctrl(void)
{
	CLKCTRL(am33xx_dcan0_hwmod, AM33XX_CM_PER_DCAN0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_dcan1_hwmod, AM33XX_CM_PER_DCAN1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_elm_hwmod, AM33XX_CM_PER_ELM_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_epwmss0_hwmod, AM33XX_CM_PER_EPWMSS0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_epwmss1_hwmod, AM33XX_CM_PER_EPWMSS1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_epwmss2_hwmod, AM33XX_CM_PER_EPWMSS2_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_gpio1_hwmod, AM33XX_CM_PER_GPIO1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_gpio2_hwmod, AM33XX_CM_PER_GPIO2_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_gpio3_hwmod, AM33XX_CM_PER_GPIO3_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_mailbox_hwmod, AM33XX_CM_PER_MAILBOX0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_mcasp0_hwmod, AM33XX_CM_PER_MCASP0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_mcasp1_hwmod, AM33XX_CM_PER_MCASP1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_spi0_hwmod, AM33XX_CM_PER_SPI0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_spi1_hwmod, AM33XX_CM_PER_SPI1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_spinlock_hwmod, AM33XX_CM_PER_SPINLOCK_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer2_hwmod, AM33XX_CM_PER_TIMER2_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer3_hwmod, AM33XX_CM_PER_TIMER3_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer4_hwmod, AM33XX_CM_PER_TIMER4_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer5_hwmod, AM33XX_CM_PER_TIMER5_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer6_hwmod, AM33XX_CM_PER_TIMER6_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer7_hwmod, AM33XX_CM_PER_TIMER7_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_smartreflex0_hwmod,
		AM33XX_CM_WKUP_SMARTREFLEX0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_smartreflex1_hwmod,
		AM33XX_CM_WKUP_SMARTREFLEX1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_timer1_hwmod, AM33XX_CM_WKUP_TIMER1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_wd_timer1_hwmod, AM33XX_CM_WKUP_WDT1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_rtc_hwmod, AM33XX_CM_RTC_RTC_CLKCTRL_OFFSET);
	PRCM_FLAGS(am33xx_rtc_hwmod, HWMOD_OMAP4_ZERO_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_gpmc_hwmod, AM33XX_CM_PER_GPMC_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_l4_ls_hwmod, AM33XX_CM_PER_L4LS_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_l4_wkup_hwmod, AM33XX_CM_WKUP_L4WKUP_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_l3_main_hwmod, AM33XX_CM_PER_L3_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_tpcc_hwmod, AM33XX_CM_PER_TPCC_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_tptc0_hwmod, AM33XX_CM_PER_TPTC0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_tptc1_hwmod, AM33XX_CM_PER_TPTC1_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_tptc2_hwmod, AM33XX_CM_PER_TPTC2_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_gfx_hwmod, AM33XX_CM_GFX_GFX_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_pruss_hwmod, AM33XX_CM_PER_PRUSS_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_mpu_hwmod , AM33XX_CM_MPU_MPU_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_l3_instr_hwmod , AM33XX_CM_PER_L3_INSTR_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_ocmcram_hwmod , AM33XX_CM_PER_OCMCRAM_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_sha0_hwmod , AM33XX_CM_PER_SHA0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_aes0_hwmod , AM33XX_CM_PER_AES0_CLKCTRL_OFFSET);
	CLKCTRL(am33xx_rng_hwmod, AM33XX_CM_PER_RNG_CLKCTRL_OFFSET);
}