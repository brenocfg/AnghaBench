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
 int PM_CLK_GATE_REG_OFFSET_USB_HOST ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cns3xxx_pwr_clk_dis (int) ; 
 int /*<<< orphan*/  usb_pwr_ref ; 

__attribute__((used)) static void csn3xxx_usb_power_off(struct platform_device *pdev)
{
	/*
	 * EHCI and OHCI share the same clock and power,
	 * resetting twice would cause the 1st controller been reset.
	 * Therefore only do power up  at the first up device, and
	 * power down at the last down device.
	 */
	if (atomic_dec_return(&usb_pwr_ref) == 0)
		cns3xxx_pwr_clk_dis(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
}