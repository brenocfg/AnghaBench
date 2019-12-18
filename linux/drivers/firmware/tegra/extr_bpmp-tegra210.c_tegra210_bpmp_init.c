#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int count; } ;
struct tegra_bpmp {int /*<<< orphan*/ * threaded_channels; TYPE_6__* soc; TYPE_3__ threaded; int /*<<< orphan*/ * rx_channel; int /*<<< orphan*/ * tx_channel; struct tegra210_bpmp* priv; int /*<<< orphan*/  dev; } ;
struct tegra210_bpmp {int /*<<< orphan*/  tx_irq_data; void* arb_sema; void* atomics; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {unsigned int offset; } ;
struct TYPE_8__ {unsigned int offset; } ;
struct TYPE_7__ {unsigned int offset; } ;
struct TYPE_11__ {TYPE_4__ thread; TYPE_2__ cpu_rx; TYPE_1__ cpu_tx; } ;
struct TYPE_12__ {TYPE_5__ channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra210_bpmp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_bpmp*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rx_irq ; 
 int tegra210_bpmp_channel_init (int /*<<< orphan*/ *,struct tegra_bpmp*,unsigned int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra210_bpmp_init(struct tegra_bpmp *bpmp)
{
	struct platform_device *pdev = to_platform_device(bpmp->dev);
	struct tegra210_bpmp *priv;
	struct resource *res;
	unsigned int i;
	int err;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	bpmp->priv = priv;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->atomics = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->atomics))
		return PTR_ERR(priv->atomics);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->arb_sema = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->arb_sema))
		return PTR_ERR(priv->arb_sema);

	err = tegra210_bpmp_channel_init(bpmp->tx_channel, bpmp,
					 bpmp->soc->channels.cpu_tx.offset);
	if (err < 0)
		return err;

	err = tegra210_bpmp_channel_init(bpmp->rx_channel, bpmp,
					 bpmp->soc->channels.cpu_rx.offset);
	if (err < 0)
		return err;

	for (i = 0; i < bpmp->threaded.count; i++) {
		unsigned int index = bpmp->soc->channels.thread.offset + i;

		err = tegra210_bpmp_channel_init(&bpmp->threaded_channels[i],
						 bpmp, index);
		if (err < 0)
			return err;
	}

	err = platform_get_irq_byname(pdev, "tx");
	if (err < 0) {
		dev_err(&pdev->dev, "failed to get TX IRQ: %d\n", err);
		return err;
	}

	priv->tx_irq_data = irq_get_irq_data(err);
	if (!priv->tx_irq_data) {
		dev_err(&pdev->dev, "failed to get IRQ data for TX IRQ\n");
		return err;
	}

	err = platform_get_irq_byname(pdev, "rx");
	if (err < 0) {
		dev_err(&pdev->dev, "failed to get rx IRQ: %d\n", err);
		return err;
	}

	err = devm_request_irq(&pdev->dev, err, rx_irq,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), bpmp);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", err);
		return err;
	}

	return 0;
}