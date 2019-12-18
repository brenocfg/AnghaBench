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
 int IMX_CHIP_REVISION_1_0 ; 
 int IMX_CHIP_REVISION_2_0 ; 
 int IMX_CHIP_REVISION_2_1 ; 
 int IMX_CHIP_REVISION_UNKNOWN ; 
 int /*<<< orphan*/  MX27_IO_ADDRESS (scalar_t__) ; 
 scalar_t__ MX27_SYSCTRL_BASE_ADDR ; 
 scalar_t__ SYS_CHIP_ID ; 
 int imx_readl (int /*<<< orphan*/ ) ; 
 int mx27_cpu_partnumber ; 

__attribute__((used)) static int mx27_read_cpu_rev(void)
{
	u32 val;
	/*
	 * now we have access to the IO registers. As we need
	 * the silicon revision very early we read it here to
	 * avoid any further hooks
	*/
	val = imx_readl(MX27_IO_ADDRESS(MX27_SYSCTRL_BASE_ADDR + SYS_CHIP_ID));

	mx27_cpu_partnumber = (int)((val >> 12) & 0xFFFF);

	switch (val >> 28) {
	case 0:
		return IMX_CHIP_REVISION_1_0;
	case 1:
		return IMX_CHIP_REVISION_2_0;
	case 2:
		return IMX_CHIP_REVISION_2_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}