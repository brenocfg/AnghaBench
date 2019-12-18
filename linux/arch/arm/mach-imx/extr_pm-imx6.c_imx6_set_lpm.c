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
typedef  enum mxc_cpu_pwr_mode { ____Placeholder_mxc_cpu_pwr_mode } mxc_cpu_pwr_mode ;

/* Variables and functions */
 int BM_CLPCR_ARM_CLK_DIS_ON_LPM ; 
 int BM_CLPCR_BYPASS_PMIC_READY ; 
 int BM_CLPCR_BYP_MMDC_CH0_LPM_HS ; 
 int BM_CLPCR_BYP_MMDC_CH1_LPM_HS ; 
 int BM_CLPCR_LPM ; 
 int BM_CLPCR_SBYOS ; 
 int BM_CLPCR_VSTBY ; 
 int BP_CLPCR_LPM ; 
 int BP_CLPCR_STBY_COUNT ; 
 scalar_t__ CLPCR ; 
 int EINVAL ; 
#define  STOP_POWER_OFF 132 
#define  STOP_POWER_ON 131 
#define  WAIT_CLOCKED 130 
#define  WAIT_UNCLOCKED 129 
#define  WAIT_UNCLOCKED_POWER_OFF 128 
 scalar_t__ ccm_base ; 
 int /*<<< orphan*/  cpu_is_imx6sl () ; 
 int /*<<< orphan*/  cpu_is_imx6sll () ; 
 int /*<<< orphan*/  cpu_is_imx6sx () ; 
 int /*<<< orphan*/  cpu_is_imx6ul () ; 
 int /*<<< orphan*/  cpu_is_imx6ull () ; 
 int /*<<< orphan*/  cpu_is_imx6ulz () ; 
 int /*<<< orphan*/  imx_gpc_hwirq_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_gpc_hwirq_unmask (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

int imx6_set_lpm(enum mxc_cpu_pwr_mode mode)
{
	u32 val = readl_relaxed(ccm_base + CLPCR);

	val &= ~BM_CLPCR_LPM;
	switch (mode) {
	case WAIT_CLOCKED:
		break;
	case WAIT_UNCLOCKED:
		val |= 0x1 << BP_CLPCR_LPM;
		val |= BM_CLPCR_ARM_CLK_DIS_ON_LPM;
		break;
	case STOP_POWER_ON:
		val |= 0x2 << BP_CLPCR_LPM;
		val &= ~BM_CLPCR_VSTBY;
		val &= ~BM_CLPCR_SBYOS;
		if (cpu_is_imx6sl())
			val |= BM_CLPCR_BYPASS_PMIC_READY;
		if (cpu_is_imx6sl() || cpu_is_imx6sx() || cpu_is_imx6ul() ||
		    cpu_is_imx6ull() || cpu_is_imx6sll() || cpu_is_imx6ulz())
			val |= BM_CLPCR_BYP_MMDC_CH0_LPM_HS;
		else
			val |= BM_CLPCR_BYP_MMDC_CH1_LPM_HS;
		break;
	case WAIT_UNCLOCKED_POWER_OFF:
		val |= 0x1 << BP_CLPCR_LPM;
		val &= ~BM_CLPCR_VSTBY;
		val &= ~BM_CLPCR_SBYOS;
		break;
	case STOP_POWER_OFF:
		val |= 0x2 << BP_CLPCR_LPM;
		val |= 0x3 << BP_CLPCR_STBY_COUNT;
		val |= BM_CLPCR_VSTBY;
		val |= BM_CLPCR_SBYOS;
		if (cpu_is_imx6sl() || cpu_is_imx6sx())
			val |= BM_CLPCR_BYPASS_PMIC_READY;
		if (cpu_is_imx6sl() || cpu_is_imx6sx() || cpu_is_imx6ul() ||
		    cpu_is_imx6ull() || cpu_is_imx6sll() || cpu_is_imx6ulz())
			val |= BM_CLPCR_BYP_MMDC_CH0_LPM_HS;
		else
			val |= BM_CLPCR_BYP_MMDC_CH1_LPM_HS;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * ERR007265: CCM: When improper low-power sequence is used,
	 * the SoC enters low power mode before the ARM core executes WFI.
	 *
	 * Software workaround:
	 * 1) Software should trigger IRQ #32 (IOMUX) to be always pending
	 *    by setting IOMUX_GPR1_GINT.
	 * 2) Software should then unmask IRQ #32 in GPC before setting CCM
	 *    Low-Power mode.
	 * 3) Software should mask IRQ #32 right after CCM Low-Power mode
	 *    is set (set bits 0-1 of CCM_CLPCR).
	 *
	 * Note that IRQ #32 is GIC SPI #0.
	 */
	if (mode != WAIT_CLOCKED)
		imx_gpc_hwirq_unmask(0);
	writel_relaxed(val, ccm_base + CLPCR);
	if (mode != WAIT_CLOCKED)
		imx_gpc_hwirq_mask(0);

	return 0;
}