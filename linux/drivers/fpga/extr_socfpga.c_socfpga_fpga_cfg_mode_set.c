#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct socfpga_fpga_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_CDRATIO_MASK ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_CFGWDTH_MASK ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_NCE ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_OFST ; 
 TYPE_1__* cfgmgr_modes ; 
 int socfpga_fpga_cfg_mode_get (struct socfpga_fpga_priv*) ; 
 int /*<<< orphan*/  socfpga_fpga_readl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socfpga_fpga_cfg_mode_set(struct socfpga_fpga_priv *priv)
{
	u32 ctrl_reg;
	int mode;

	/* get value from MSEL pins */
	mode = socfpga_fpga_cfg_mode_get(priv);
	if (mode < 0)
		return mode;

	/* Adjust CTRL for the CDRATIO */
	ctrl_reg = socfpga_fpga_readl(priv, SOCFPGA_FPGMGR_CTL_OFST);
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_CDRATIO_MASK;
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_CFGWDTH_MASK;
	ctrl_reg |= cfgmgr_modes[mode].ctrl;

	/* Set NCE to 0. */
	ctrl_reg &= ~SOCFPGA_FPGMGR_CTL_NCE;
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_CTL_OFST, ctrl_reg);

	return 0;
}