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
 unsigned int AXI_CLKGEN_V2_DRP_CNTRL_SEL ; 
 int /*<<< orphan*/  AXI_CLKGEN_V2_REG_DRP_CNTRL ; 
 int /*<<< orphan*/  axi_clkgen_mmcm_read (struct axi_clkgen*,unsigned int,unsigned int*) ; 
 int axi_clkgen_wait_non_busy (struct axi_clkgen*) ; 
 int /*<<< orphan*/  axi_clkgen_write (struct axi_clkgen*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int axi_clkgen_mmcm_write(struct axi_clkgen *axi_clkgen,
	unsigned int reg, unsigned int val, unsigned int mask)
{
	unsigned int reg_val = 0;
	int ret;

	ret = axi_clkgen_wait_non_busy(axi_clkgen);
	if (ret < 0)
		return ret;

	if (mask != 0xffff) {
		axi_clkgen_mmcm_read(axi_clkgen, reg, &reg_val);
		reg_val &= ~mask;
	}

	reg_val |= AXI_CLKGEN_V2_DRP_CNTRL_SEL | (reg << 16) | (val & mask);

	axi_clkgen_write(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_CNTRL, reg_val);

	return 0;
}