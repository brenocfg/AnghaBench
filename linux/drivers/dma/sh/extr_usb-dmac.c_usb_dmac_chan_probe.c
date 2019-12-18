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
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct usb_dmac_chan {unsigned int index; int /*<<< orphan*/  desc_got; int /*<<< orphan*/  desc_freed; TYPE_1__ vc; int /*<<< orphan*/  irq; scalar_t__ iomem; } ;
struct usb_dmac {int /*<<< orphan*/  engine; int /*<<< orphan*/  dev; scalar_t__ iomem; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ USB_DMAC_CHAN_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 char* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dmac_isr_channel ; 
 int /*<<< orphan*/  usb_dmac_virt_desc_free ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_dmac_chan_probe(struct usb_dmac *dmac,
			       struct usb_dmac_chan *uchan,
			       unsigned int index)
{
	struct platform_device *pdev = to_platform_device(dmac->dev);
	char pdev_irqname[5];
	char *irqname;
	int ret;

	uchan->index = index;
	uchan->iomem = dmac->iomem + USB_DMAC_CHAN_OFFSET(index);

	/* Request the channel interrupt. */
	sprintf(pdev_irqname, "ch%u", index);
	uchan->irq = platform_get_irq_byname(pdev, pdev_irqname);
	if (uchan->irq < 0)
		return -ENODEV;

	irqname = devm_kasprintf(dmac->dev, GFP_KERNEL, "%s:%u",
				 dev_name(dmac->dev), index);
	if (!irqname)
		return -ENOMEM;

	ret = devm_request_irq(dmac->dev, uchan->irq, usb_dmac_isr_channel,
			       IRQF_SHARED, irqname, uchan);
	if (ret) {
		dev_err(dmac->dev, "failed to request IRQ %u (%d)\n",
			uchan->irq, ret);
		return ret;
	}

	uchan->vc.desc_free = usb_dmac_virt_desc_free;
	vchan_init(&uchan->vc, &dmac->engine);
	INIT_LIST_HEAD(&uchan->desc_freed);
	INIT_LIST_HEAD(&uchan->desc_got);

	return 0;
}