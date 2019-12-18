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
struct tcs_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; int /*<<< orphan*/  member_0; } ;
struct clk_rpmh {int aggr_state; int last_sent_aggr_state; int /*<<< orphan*/  res_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  res_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_TCS_CMD (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPMH_ACTIVE_ONLY_STATE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmh_clk_lock ; 
 int rpmh_write_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcs_cmd*,int) ; 

__attribute__((used)) static int clk_rpmh_bcm_send_cmd(struct clk_rpmh *c, bool enable)
{
	struct tcs_cmd cmd = { 0 };
	u32 cmd_state;
	int ret;

	mutex_lock(&rpmh_clk_lock);

	cmd_state = 0;
	if (enable) {
		cmd_state = 1;
		if (c->aggr_state)
			cmd_state = c->aggr_state;
	}

	if (c->last_sent_aggr_state == cmd_state) {
		mutex_unlock(&rpmh_clk_lock);
		return 0;
	}

	cmd.addr = c->res_addr;
	cmd.data = BCM_TCS_CMD(1, enable, 0, cmd_state);

	ret = rpmh_write_async(c->dev, RPMH_ACTIVE_ONLY_STATE, &cmd, 1);
	if (ret) {
		dev_err(c->dev, "set active state of %s failed: (%d)\n",
			c->res_name, ret);
		mutex_unlock(&rpmh_clk_lock);
		return ret;
	}

	c->last_sent_aggr_state = cmd_state;

	mutex_unlock(&rpmh_clk_lock);

	return 0;
}