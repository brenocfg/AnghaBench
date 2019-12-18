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
struct uniphier_mdmac_device {int /*<<< orphan*/  ddev; scalar_t__ reg_base; struct uniphier_mdmac_chan* channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct uniphier_mdmac_chan {int chan_id; TYPE_1__ vc; scalar_t__ reg_ch_base; struct uniphier_mdmac_device* mdev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ UNIPHIER_MDMAC_CH_OFFSET ; 
 int UNIPHIER_MDMAC_CH_STRIDE ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uniphier_mdmac_chan*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  uniphier_mdmac_desc_free ; 
 int /*<<< orphan*/  uniphier_mdmac_interrupt ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_mdmac_chan_init(struct platform_device *pdev,
				    struct uniphier_mdmac_device *mdev,
				    int chan_id)
{
	struct device *dev = &pdev->dev;
	struct uniphier_mdmac_chan *mc = &mdev->channels[chan_id];
	char *irq_name;
	int irq, ret;

	irq = platform_get_irq(pdev, chan_id);
	if (irq < 0)
		return irq;

	irq_name = devm_kasprintf(dev, GFP_KERNEL, "uniphier-mio-dmac-ch%d",
				  chan_id);
	if (!irq_name)
		return -ENOMEM;

	ret = devm_request_irq(dev, irq, uniphier_mdmac_interrupt,
			       IRQF_SHARED, irq_name, mc);
	if (ret)
		return ret;

	mc->mdev = mdev;
	mc->reg_ch_base = mdev->reg_base + UNIPHIER_MDMAC_CH_OFFSET +
					UNIPHIER_MDMAC_CH_STRIDE * chan_id;
	mc->chan_id = chan_id;
	mc->vc.desc_free = uniphier_mdmac_desc_free;
	vchan_init(&mc->vc, &mdev->ddev);

	return 0;
}