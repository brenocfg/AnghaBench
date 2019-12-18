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
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_cvp_conf* priv; } ;
struct fpga_image_info {int dummy; } ;
struct altera_cvp_conf {TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll_time_us; int /*<<< orphan*/  (* switch_clk ) (struct altera_cvp_conf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL ; 
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL_CONFIG ; 
 int /*<<< orphan*/  VSE_CVP_PROG_CTRL_START_XFER ; 
 int /*<<< orphan*/  VSE_CVP_STATUS_CFG_RDY ; 
 int altera_cvp_wait_status (struct altera_cvp_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  altera_read_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  altera_write_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct altera_cvp_conf*) ; 

__attribute__((used)) static int altera_cvp_teardown(struct fpga_manager *mgr,
			       struct fpga_image_info *info)
{
	struct altera_cvp_conf *conf = mgr->priv;
	int ret;
	u32 val;

	/* STEP 12 - reset START_XFER bit */
	altera_read_config_dword(conf, VSE_CVP_PROG_CTRL, &val);
	val &= ~VSE_CVP_PROG_CTRL_START_XFER;
	altera_write_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/* STEP 13 - reset CVP_CONFIG bit */
	val &= ~VSE_CVP_PROG_CTRL_CONFIG;
	altera_write_config_dword(conf, VSE_CVP_PROG_CTRL, val);

	/*
	 * STEP 14
	 * - set CVP_NUMCLKS to 1 and then issue CVP_DUMMY_WR dummy
	 *   writes to the HIP
	 */
	if (conf->priv->switch_clk)
		conf->priv->switch_clk(conf);

	/* STEP 15 - poll CVP_CONFIG_READY bit for 0 with 10us timeout */
	ret = altera_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_RDY, 0,
				     conf->priv->poll_time_us);
	if (ret)
		dev_err(&mgr->dev, "CFG_RDY == 0 timeout\n");

	return ret;
}