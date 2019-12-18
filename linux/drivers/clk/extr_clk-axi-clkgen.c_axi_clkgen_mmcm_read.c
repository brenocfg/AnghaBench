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
struct axi_clkgen {int dummy; } ;

/* Variables and functions */
 unsigned int AXI_CLKGEN_V2_DRP_CNTRL_READ ; 
 unsigned int AXI_CLKGEN_V2_DRP_CNTRL_SEL ; 
 int /*<<< orphan*/  AXI_CLKGEN_V2_REG_DRP_CNTRL ; 
 int axi_clkgen_wait_non_busy (struct axi_clkgen*) ; 
 int /*<<< orphan*/  axi_clkgen_write (struct axi_clkgen*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int axi_clkgen_mmcm_read(struct axi_clkgen *axi_clkgen,
	unsigned int reg, unsigned int *val)
{
	unsigned int reg_val;
	int ret;

	ret = axi_clkgen_wait_non_busy(axi_clkgen);
	if (ret < 0)
		return ret;

	reg_val = AXI_CLKGEN_V2_DRP_CNTRL_SEL | AXI_CLKGEN_V2_DRP_CNTRL_READ;
	reg_val |= (reg << 16);

	axi_clkgen_write(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_CNTRL, reg_val);

	ret = axi_clkgen_wait_non_busy(axi_clkgen);
	if (ret < 0)
		return ret;

	*val = ret;

	return 0;
}