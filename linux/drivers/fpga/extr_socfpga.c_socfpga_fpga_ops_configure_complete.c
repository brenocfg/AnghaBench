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
struct socfpga_fpga_priv {int dummy; } ;
struct fpga_manager {struct socfpga_fpga_priv* priv; } ;
struct fpga_image_info {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_AXICFGEN ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_EN ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_CTL_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_STAT_USER_MODE ; 
 int /*<<< orphan*/  socfpga_fpga_clr_bitsl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socfpga_fpga_dclk_set_and_wait_clear (struct socfpga_fpga_priv*,int) ; 
 int socfpga_fpga_wait_for_config_done (struct socfpga_fpga_priv*) ; 
 scalar_t__ socfpga_fpga_wait_for_state (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socfpga_fpga_ops_configure_complete(struct fpga_manager *mgr,
					       struct fpga_image_info *info)
{
	struct socfpga_fpga_priv *priv = mgr->priv;
	u32 status;

	/*
	 * Step 10:
	 *  - Observe CONF_DONE and nSTATUS (active low)
	 *  - if CONF_DONE = 1 and nSTATUS = 1, configuration was successful
	 *  - if CONF_DONE = 0 and nSTATUS = 0, configuration failed
	 */
	status = socfpga_fpga_wait_for_config_done(priv);
	if (status)
		return status;

	/* Step 11: Clear CTRL.AXICFGEN to disable transfer of config data */
	socfpga_fpga_clr_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_AXICFGEN);

	/*
	 * Step 12:
	 *  - Write 4 to DCLKCNT
	 *  - Wait for STATUS.DCNTDONE = 1
	 *  - Clear W1C bit in STATUS.DCNTDONE
	 */
	if (socfpga_fpga_dclk_set_and_wait_clear(priv, 4))
		return -ETIMEDOUT;

	/* Step 13: Wait for STATUS.MODE to report USER MODE */
	if (socfpga_fpga_wait_for_state(priv, SOCFPGA_FPGMGR_STAT_USER_MODE))
		return -ETIMEDOUT;

	/* Step 14: Set CTRL.EN to 0 */
	socfpga_fpga_clr_bitsl(priv, SOCFPGA_FPGMGR_CTL_OFST,
			       SOCFPGA_FPGMGR_CTL_EN);

	return 0;
}