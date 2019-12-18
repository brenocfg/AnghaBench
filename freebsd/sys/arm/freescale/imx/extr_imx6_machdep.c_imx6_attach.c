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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_TMR_FREQUENCY_VARIES ; 
 int /*<<< orphan*/  arm_tmr_change_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_fdt_interrupt_data () ; 
 int /*<<< orphan*/  fix_fdt_iomuxc_data () ; 

__attribute__((used)) static int
imx6_attach(platform_t plat)
{

	/* Fix soc interrupt-parent property. */
	fix_fdt_interrupt_data();

	/* Fix iomuxc-gpr and iomuxc nodes both using the same mmio range. */
	fix_fdt_iomuxc_data();

	/* Inform the MPCore timer driver that its clock is variable. */
	arm_tmr_change_frequency(ARM_TMR_FREQUENCY_VARIES);

	return (0);
}