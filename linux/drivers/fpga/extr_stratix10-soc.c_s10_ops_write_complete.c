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
struct TYPE_2__ {struct device* dev; } ;
struct s10_priv {int /*<<< orphan*/  chan; int /*<<< orphan*/  status; int /*<<< orphan*/  status_return_completion; TYPE_1__ client; } ;
struct fpga_manager {struct s10_priv* priv; } ;
struct fpga_image_info {int /*<<< orphan*/  config_complete_timeout_us; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_RECONFIG_STATUS ; 
 int EFAULT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SVC_STATUS_RECONFIG_COMPLETED ; 
 int /*<<< orphan*/  SVC_STATUS_RECONFIG_ERROR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int s10_svc_send_msg (struct s10_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stratix10_svc_done (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s10_ops_write_complete(struct fpga_manager *mgr,
				  struct fpga_image_info *info)
{
	struct s10_priv *priv = mgr->priv;
	struct device *dev = priv->client.dev;
	unsigned long timeout;
	int ret;

	timeout = usecs_to_jiffies(info->config_complete_timeout_us);

	do {
		reinit_completion(&priv->status_return_completion);

		ret = s10_svc_send_msg(priv, COMMAND_RECONFIG_STATUS, NULL, 0);
		if (ret < 0)
			break;

		ret = wait_for_completion_interruptible_timeout(
			&priv->status_return_completion, timeout);
		if (!ret) {
			dev_err(dev,
				"timeout waiting for RECONFIG_COMPLETED\n");
			ret = -ETIMEDOUT;
			break;
		}
		if (ret < 0) {
			dev_err(dev,
				"error (%d) waiting for RECONFIG_COMPLETED\n",
				ret);
			break;
		}
		/* Not error or timeout, so ret is # of jiffies until timeout */
		timeout = ret;
		ret = 0;

		if (test_and_clear_bit(SVC_STATUS_RECONFIG_COMPLETED,
				       &priv->status))
			break;

		if (test_and_clear_bit(SVC_STATUS_RECONFIG_ERROR,
				       &priv->status)) {
			dev_err(dev, "ERROR - giving up - SVC_STATUS_RECONFIG_ERROR\n");
			ret = -EFAULT;
			break;
		}
	} while (1);

	stratix10_svc_done(priv->chan);

	return ret;
}