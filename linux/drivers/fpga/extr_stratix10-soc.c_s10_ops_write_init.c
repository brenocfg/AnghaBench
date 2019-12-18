#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct stratix10_svc_command_config_type {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct device* dev; } ;
struct s10_priv {int /*<<< orphan*/  chan; TYPE_2__* svc_bufs; int /*<<< orphan*/  status; int /*<<< orphan*/  status_return_completion; TYPE_1__ client; } ;
struct fpga_manager {struct s10_priv* priv; } ;
struct fpga_image_info {int flags; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ctype ;
struct TYPE_4__ {char* buf; scalar_t__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMMAND_RECONFIG ; 
 int /*<<< orphan*/  COMMAND_RECONFIG_FLAG_PARTIAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 size_t NUM_SVC_BUFS ; 
 int /*<<< orphan*/  S10_RECONFIG_TIMEOUT ; 
 int /*<<< orphan*/  SVC_BUF_SIZE ; 
 int /*<<< orphan*/  SVC_STATUS_RECONFIG_REQUEST_OK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s10_free_buffers (struct fpga_manager*) ; 
 int s10_svc_send_msg (struct s10_priv*,int /*<<< orphan*/ ,struct stratix10_svc_command_config_type*,int) ; 
 char* stratix10_svc_allocate_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stratix10_svc_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s10_ops_write_init(struct fpga_manager *mgr,
			      struct fpga_image_info *info,
			      const char *buf, size_t count)
{
	struct s10_priv *priv = mgr->priv;
	struct device *dev = priv->client.dev;
	struct stratix10_svc_command_config_type ctype;
	char *kbuf;
	uint i;
	int ret;

	ctype.flags = 0;
	if (info->flags & FPGA_MGR_PARTIAL_RECONFIG) {
		dev_dbg(dev, "Requesting partial reconfiguration.\n");
		ctype.flags |= BIT(COMMAND_RECONFIG_FLAG_PARTIAL);
	} else {
		dev_dbg(dev, "Requesting full reconfiguration.\n");
	}

	reinit_completion(&priv->status_return_completion);
	ret = s10_svc_send_msg(priv, COMMAND_RECONFIG,
			       &ctype, sizeof(ctype));
	if (ret < 0)
		goto init_done;

	ret = wait_for_completion_interruptible_timeout(
		&priv->status_return_completion, S10_RECONFIG_TIMEOUT);
	if (!ret) {
		dev_err(dev, "timeout waiting for RECONFIG_REQUEST\n");
		ret = -ETIMEDOUT;
		goto init_done;
	}
	if (ret < 0) {
		dev_err(dev, "error (%d) waiting for RECONFIG_REQUEST\n", ret);
		goto init_done;
	}

	ret = 0;
	if (!test_and_clear_bit(SVC_STATUS_RECONFIG_REQUEST_OK,
				&priv->status)) {
		ret = -ETIMEDOUT;
		goto init_done;
	}

	/* Allocate buffers from the service layer's pool. */
	for (i = 0; i < NUM_SVC_BUFS; i++) {
		kbuf = stratix10_svc_allocate_memory(priv->chan, SVC_BUF_SIZE);
		if (!kbuf) {
			s10_free_buffers(mgr);
			ret = -ENOMEM;
			goto init_done;
		}

		priv->svc_bufs[i].buf = kbuf;
		priv->svc_bufs[i].lock = 0;
	}

init_done:
	stratix10_svc_done(priv->chan);
	return ret;
}