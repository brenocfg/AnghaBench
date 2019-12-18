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
typedef  int u32 ;
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_cvp_conf* priv; } ;
struct fpga_image_info {int dummy; } ;
struct altera_cvp_conf {TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_time_us; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  VSE_CVP_MODE_CTRL ; 
 int VSE_CVP_MODE_CTRL_CVP_MODE ; 
 int VSE_CVP_MODE_CTRL_HIP_CLK_SEL ; 
 int VSE_CVP_STATUS_PLD_CLK_IN_USE ; 
 int VSE_CVP_STATUS_USERMODE ; 
 int VSE_UNCOR_ERR_CVP_CFG_ERR ; 
 int /*<<< orphan*/  VSE_UNCOR_ERR_STATUS ; 
 int altera_cvp_teardown (struct fpga_manager*,struct fpga_image_info*) ; 
 int altera_cvp_wait_status (struct altera_cvp_conf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  altera_read_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  altera_write_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int altera_cvp_write_complete(struct fpga_manager *mgr,
				     struct fpga_image_info *info)
{
	struct altera_cvp_conf *conf = mgr->priv;
	u32 mask, val;
	int ret;

	ret = altera_cvp_teardown(mgr, info);
	if (ret)
		return ret;

	/* STEP 16 - check CVP_CONFIG_ERROR_LATCHED bit */
	altera_read_config_dword(conf, VSE_UNCOR_ERR_STATUS, &val);
	if (val & VSE_UNCOR_ERR_CVP_CFG_ERR) {
		dev_err(&mgr->dev, "detected CVP_CONFIG_ERROR_LATCHED!\n");
		return -EPROTO;
	}

	/* STEP 17 - reset CVP_MODE and HIP_CLK_SEL bit */
	altera_read_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_HIP_CLK_SEL;
	val &= ~VSE_CVP_MODE_CTRL_CVP_MODE;
	altera_write_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	/* STEP 18 - poll PLD_CLK_IN_USE and USER_MODE bits */
	mask = VSE_CVP_STATUS_PLD_CLK_IN_USE | VSE_CVP_STATUS_USERMODE;
	ret = altera_cvp_wait_status(conf, mask, mask,
				     conf->priv->user_time_us);
	if (ret)
		dev_err(&mgr->dev, "PLD_CLK_IN_USE|USERMODE timeout\n");

	return ret;
}