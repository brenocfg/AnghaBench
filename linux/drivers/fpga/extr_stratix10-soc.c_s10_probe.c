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
struct TYPE_2__ {struct s10_priv* priv; int /*<<< orphan*/  receive_cb; struct device* dev; } ;
struct s10_priv {int /*<<< orphan*/  chan; int /*<<< orphan*/  status_return_completion; TYPE_1__ client; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVC_CLIENT_FPGA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct s10_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct fpga_manager* fpga_mgr_create (struct device*,char*,int /*<<< orphan*/ *,struct s10_priv*) ; 
 int /*<<< orphan*/  fpga_mgr_free (struct fpga_manager*) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_manager*) ; 
 int /*<<< orphan*/  s10_ops ; 
 int /*<<< orphan*/  s10_receive_callback ; 
 int /*<<< orphan*/  stratix10_svc_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stratix10_svc_request_channel_byname (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s10_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct s10_priv *priv;
	struct fpga_manager *mgr;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->client.dev = dev;
	priv->client.receive_cb = s10_receive_callback;
	priv->client.priv = priv;

	priv->chan = stratix10_svc_request_channel_byname(&priv->client,
							  SVC_CLIENT_FPGA);
	if (IS_ERR(priv->chan)) {
		dev_err(dev, "couldn't get service channel (%s)\n",
			SVC_CLIENT_FPGA);
		return PTR_ERR(priv->chan);
	}

	init_completion(&priv->status_return_completion);

	mgr = fpga_mgr_create(dev, "Stratix10 SOC FPGA Manager",
			      &s10_ops, priv);
	if (!mgr) {
		dev_err(dev, "unable to create FPGA manager\n");
		ret = -ENOMEM;
		goto probe_err;
	}

	ret = fpga_mgr_register(mgr);
	if (ret) {
		dev_err(dev, "unable to register FPGA manager\n");
		fpga_mgr_free(mgr);
		goto probe_err;
	}

	platform_set_drvdata(pdev, mgr);
	return ret;

probe_err:
	stratix10_svc_free_channel(priv->chan);
	return ret;
}