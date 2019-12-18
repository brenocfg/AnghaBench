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
struct stratix10_svc_client_msg {int command; unsigned long* arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  receive_cb; } ;
struct stratix10_rsu_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  chan; TYPE_1__ client; int /*<<< orphan*/  completion; } ;
typedef  int /*<<< orphan*/  rsu_callback ;
typedef  enum stratix10_svc_command_code { ____Placeholder_stratix10_svc_command_code } stratix10_svc_command_code ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RSU_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stratix10_svc_done (int /*<<< orphan*/ ) ; 
 int stratix10_svc_send (int /*<<< orphan*/ ,struct stratix10_svc_client_msg*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsu_send_msg(struct stratix10_rsu_priv *priv,
			enum stratix10_svc_command_code command,
			unsigned long arg,
			rsu_callback callback)
{
	struct stratix10_svc_client_msg msg;
	int ret;

	mutex_lock(&priv->lock);
	reinit_completion(&priv->completion);
	priv->client.receive_cb = callback;

	msg.command = command;
	if (arg)
		msg.arg[0] = arg;

	ret = stratix10_svc_send(priv->chan, &msg);
	if (ret < 0)
		goto status_done;

	ret = wait_for_completion_interruptible_timeout(&priv->completion,
							RSU_TIMEOUT);
	if (!ret) {
		dev_err(priv->client.dev,
			"timeout waiting for SMC call\n");
		ret = -ETIMEDOUT;
		goto status_done;
	} else if (ret < 0) {
		dev_err(priv->client.dev,
			"error %d waiting for SMC call\n", ret);
		goto status_done;
	} else {
		ret = 0;
	}

status_done:
	stratix10_svc_done(priv->chan);
	mutex_unlock(&priv->lock);
	return ret;
}