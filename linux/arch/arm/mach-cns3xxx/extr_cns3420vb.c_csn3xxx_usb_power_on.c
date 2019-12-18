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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_CHIP_CONFIG_REG ; 
 int PM_CLK_GATE_REG_OFFSET_USB_HOST ; 
 int PM_PLL_HM_PD_CTRL_REG_OFFSET_PLL_USB ; 
 int PM_SOFT_RST_REG_OFFST_USB_HOST ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cns3xxx_pwr_clk_en (int) ; 
 int /*<<< orphan*/  cns3xxx_pwr_power_up (int) ; 
 int /*<<< orphan*/  cns3xxx_pwr_soft_rst (int) ; 
 int /*<<< orphan*/  usb_pwr_ref ; 

__attribute__((used)) static int csn3xxx_usb_power_on(struct platform_device *pdev)
{
	/*
	 * EHCI and OHCI share the same clock and power,
	 * resetting twice would cause the 1st controller been reset.
	 * Therefore only do power up  at the first up device, and
	 * power down at the last down device.
	 *
	 * Set USB AHB INCR length to 16
	 */
	if (atomic_inc_return(&usb_pwr_ref) == 1) {
		cns3xxx_pwr_power_up(1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_PLL_USB);
		cns3xxx_pwr_clk_en(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
		cns3xxx_pwr_soft_rst(1 << PM_SOFT_RST_REG_OFFST_USB_HOST);
		__raw_writel((__raw_readl(MISC_CHIP_CONFIG_REG) | (0X2 << 24)),
			MISC_CHIP_CONFIG_REG);
	}

	return 0;
}