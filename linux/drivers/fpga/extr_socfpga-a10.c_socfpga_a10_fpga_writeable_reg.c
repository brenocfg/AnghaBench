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
struct device {int dummy; } ;

/* Variables and functions */
#define  A10_FPGAMGR_DCLKCNT_OFST 132 
#define  A10_FPGAMGR_DCLKSTAT_OFST 131 
#define  A10_FPGAMGR_IMGCFG_CTL_00_OFST 130 
#define  A10_FPGAMGR_IMGCFG_CTL_01_OFST 129 
#define  A10_FPGAMGR_IMGCFG_CTL_02_OFST 128 

__attribute__((used)) static bool socfpga_a10_fpga_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case A10_FPGAMGR_DCLKCNT_OFST:
	case A10_FPGAMGR_DCLKSTAT_OFST:
	case A10_FPGAMGR_IMGCFG_CTL_00_OFST:
	case A10_FPGAMGR_IMGCFG_CTL_01_OFST:
	case A10_FPGAMGR_IMGCFG_CTL_02_OFST:
		return true;
	}
	return false;
}