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
typedef  int phandle_t ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_setprop (int,char*,char*,int) ; 

__attribute__((used)) static void
fix_fdt_iomuxc_data(void)
{
	phandle_t node;

	/*
	 * The linux dts defines two nodes with the same mmio address range,
	 * iomuxc-gpr and the regular iomuxc.  The -grp node is a simple_mfd and
	 * a syscon, but it only has access to a small subset of the iomuxc
	 * registers, so it can't serve as the accessor for the iomuxc driver's
	 * register IO.  But right now, the simple_mfd driver attaches first,
	 * preventing the real iomuxc driver from allocating its mmio register
	 * range because it partially overlaps with the -gpr range.
	 *
	 * For now, by far the easiest thing to do to keep imx6 working is to
	 * just disable the iomuxc-gpr node because we don't have a driver for
	 * it anyway, we just need to prevent attachment of simple_mfd.
	 *
	 * If we ever write a -gpr driver, this code should probably switch to
	 * modifying the reg property so that the range covers all the iomuxc
	 * regs, then the -gpr driver can be a regular syscon driver that iomuxc
	 * uses for register access.
	 */
	node = OF_finddevice("/soc/aips-bus@2000000/iomuxc-gpr@20e0000");
	if (node != -1)
		OF_setprop(node, "status", "disabled", sizeof("disabled"));
}