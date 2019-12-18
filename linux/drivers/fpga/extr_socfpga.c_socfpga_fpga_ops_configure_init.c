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
struct socfpga_fpga_priv {int dummy; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct socfpga_fpga_priv* priv; } ;
struct fpga_image_info {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_AXICFGEN ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_MON_NSTATUS ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_STAT_CFG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int socfpga_fpga_reset (struct fpga_manager*) ; 
 int /*<<< orphan*/  socfpga_fpga_set_bitsl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socfpga_fpga_wait_for_state (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socfpga_fpga_ops_configure_init(struct fpga_manager *mgr,
					   struct fpga_image_info *info,
					   const char *buf, size_t count)
{
	struct socfpga_fpga_priv *priv = mgr->priv;
	int ret;

	if (info->flags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_err(&mgr->dev, "Partial reconfiguration not supported.\n");
		return -EINVAL;
	}
	/* Steps 1 - 5: Reset the FPGA */
	ret = socfpga_fpga_reset(mgr);
	if (ret)
		return ret;

	/* Step 6: Wait for FPGA to enter configuration phase */
	if (socfpga_fpga_wait_for_state(priv, SOCFPGA_FPGMGR_STAT_CFG))
		return -ETIMEDOUT;

	/* Step 7: Clear nSTATUS interrupt */
	socfpga_fpga_writel(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST,
			    SOCFPGA_FPGMGR_MON_NSTATUS);

	/* Step 8: Set CTRL.AXICFGEN to 1 to enable transfer of config data */
	socfpga_fpga_set_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_AXICFGEN);

	return 0;
}