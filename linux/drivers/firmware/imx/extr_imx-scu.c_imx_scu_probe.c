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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mbox_client {int tx_block; int knows_txdone; int /*<<< orphan*/  rx_callback; struct device* dev; } ;
struct imx_sc_ipc {int /*<<< orphan*/  done; int /*<<< orphan*/  lock; struct device* dev; struct imx_sc_chan* chans; } ;
struct imx_sc_chan {int idx; int /*<<< orphan*/  ch; struct imx_sc_ipc* sc_ipc; struct mbox_client cl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SCU_MU_CHAN_NUM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct imx_sc_ipc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 struct imx_sc_ipc* imx_sc_ipc_handle ; 
 int imx_scu_enable_general_irq_channel (struct device*) ; 
 int /*<<< orphan*/  imx_scu_rx_callback ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mbox_request_channel_byname (struct mbox_client*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_scu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct imx_sc_ipc *sc_ipc;
	struct imx_sc_chan *sc_chan;
	struct mbox_client *cl;
	char *chan_name;
	int ret;
	int i;

	sc_ipc = devm_kzalloc(dev, sizeof(*sc_ipc), GFP_KERNEL);
	if (!sc_ipc)
		return -ENOMEM;

	for (i = 0; i < SCU_MU_CHAN_NUM; i++) {
		if (i < 4)
			chan_name = kasprintf(GFP_KERNEL, "tx%d", i);
		else
			chan_name = kasprintf(GFP_KERNEL, "rx%d", i - 4);

		if (!chan_name)
			return -ENOMEM;

		sc_chan = &sc_ipc->chans[i];
		cl = &sc_chan->cl;
		cl->dev = dev;
		cl->tx_block = false;
		cl->knows_txdone = true;
		cl->rx_callback = imx_scu_rx_callback;

		sc_chan->sc_ipc = sc_ipc;
		sc_chan->idx = i % 4;
		sc_chan->ch = mbox_request_channel_byname(cl, chan_name);
		if (IS_ERR(sc_chan->ch)) {
			ret = PTR_ERR(sc_chan->ch);
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to request mbox chan %s ret %d\n",
					chan_name, ret);
			return ret;
		}

		dev_dbg(dev, "request mbox chan %s\n", chan_name);
		/* chan_name is not used anymore by framework */
		kfree(chan_name);
	}

	sc_ipc->dev = dev;
	mutex_init(&sc_ipc->lock);
	init_completion(&sc_ipc->done);

	imx_sc_ipc_handle = sc_ipc;

	ret = imx_scu_enable_general_irq_channel(dev);
	if (ret)
		dev_warn(dev,
			"failed to enable general irq channel: %d\n", ret);

	dev_info(dev, "NXP i.MX SCU Initialized\n");

	return devm_of_platform_populate(dev);
}