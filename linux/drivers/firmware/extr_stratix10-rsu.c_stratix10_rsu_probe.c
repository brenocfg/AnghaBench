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
struct TYPE_3__ {scalar_t__ version; scalar_t__ state; scalar_t__ error_details; scalar_t__ error_location; scalar_t__ fail_image; scalar_t__ current_image; } ;
struct TYPE_4__ {struct stratix10_rsu_priv* priv; int /*<<< orphan*/ * receive_cb; struct device* dev; } ;
struct stratix10_rsu_priv {int /*<<< orphan*/  chan; TYPE_1__ status; int /*<<< orphan*/  completion; TYPE_2__ client; int /*<<< orphan*/  lock; int /*<<< orphan*/  retry_counter; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_RSU_RETRY ; 
 int /*<<< orphan*/  COMMAND_RSU_STATUS ; 
 int ENOMEM ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INVALID_RETRY_COUNTER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSU_FW_VERSION_MASK ; 
 int SVC_CLIENT_RSU ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct stratix10_rsu_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stratix10_rsu_priv*) ; 
 int /*<<< orphan*/  rsu_retry_callback ; 
 int rsu_send_msg (struct stratix10_rsu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_status_callback ; 
 int /*<<< orphan*/  stratix10_svc_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stratix10_svc_request_channel_byname (TYPE_2__*,int) ; 

__attribute__((used)) static int stratix10_rsu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stratix10_rsu_priv *priv;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->client.dev = dev;
	priv->client.receive_cb = NULL;
	priv->client.priv = priv;
	priv->status.current_image = 0;
	priv->status.fail_image = 0;
	priv->status.error_location = 0;
	priv->status.error_details = 0;
	priv->status.version = 0;
	priv->status.state = 0;
	priv->retry_counter = INVALID_RETRY_COUNTER;

	mutex_init(&priv->lock);
	priv->chan = stratix10_svc_request_channel_byname(&priv->client,
							  SVC_CLIENT_RSU);
	if (IS_ERR(priv->chan)) {
		dev_err(dev, "couldn't get service channel %s\n",
			SVC_CLIENT_RSU);
		return PTR_ERR(priv->chan);
	}

	init_completion(&priv->completion);
	platform_set_drvdata(pdev, priv);

	/* get the initial state from firmware */
	ret = rsu_send_msg(priv, COMMAND_RSU_STATUS,
			   0, rsu_status_callback);
	if (ret) {
		dev_err(dev, "Error, getting RSU status %i\n", ret);
		stratix10_svc_free_channel(priv->chan);
	}

	/* only 19.3 or late version FW supports retry counter feature */
	if (FIELD_GET(RSU_FW_VERSION_MASK, priv->status.version)) {
		ret = rsu_send_msg(priv, COMMAND_RSU_RETRY, 0,
				   rsu_retry_callback);
		if (ret) {
			dev_err(dev,
				"Error, getting RSU retry %i\n", ret);
			stratix10_svc_free_channel(priv->chan);
		}
	}

	return ret;
}