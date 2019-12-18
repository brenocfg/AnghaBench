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
struct imx_sc_rpc_msg {int func; } ;
struct imx_sc_ipc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; scalar_t__ count; void* msg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MAX_RX_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int imx_sc_to_linux_errno (int) ; 
 int imx_scu_ipc_write (struct imx_sc_ipc*,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int imx_scu_call_rpc(struct imx_sc_ipc *sc_ipc, void *msg, bool have_resp)
{
	struct imx_sc_rpc_msg *hdr;
	int ret;

	if (WARN_ON(!sc_ipc || !msg))
		return -EINVAL;

	mutex_lock(&sc_ipc->lock);
	reinit_completion(&sc_ipc->done);

	sc_ipc->msg = msg;
	sc_ipc->count = 0;
	ret = imx_scu_ipc_write(sc_ipc, msg);
	if (ret < 0) {
		dev_err(sc_ipc->dev, "RPC send msg failed: %d\n", ret);
		goto out;
	}

	if (have_resp) {
		if (!wait_for_completion_timeout(&sc_ipc->done,
						 MAX_RX_TIMEOUT)) {
			dev_err(sc_ipc->dev, "RPC send msg timeout\n");
			mutex_unlock(&sc_ipc->lock);
			return -ETIMEDOUT;
		}

		/* response status is stored in hdr->func field */
		hdr = msg;
		ret = hdr->func;
	}

out:
	mutex_unlock(&sc_ipc->lock);

	dev_dbg(sc_ipc->dev, "RPC SVC done\n");

	return imx_sc_to_linux_errno(ret);
}