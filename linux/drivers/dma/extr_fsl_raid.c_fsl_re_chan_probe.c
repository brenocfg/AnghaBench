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
typedef  int u8 ;
typedef  int u32 ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dma_device {int dummy; } ;
struct fsl_re_drv_private {int /*<<< orphan*/  hw_desc_pool; struct fsl_re_chan** re_jrs; scalar_t__ re_regs; struct dma_device dma_dev; } ;
struct fsl_re_chan_cfg {int /*<<< orphan*/  jr_command; int /*<<< orphan*/  jr_config_1; int /*<<< orphan*/  oubring_size; int /*<<< orphan*/  inbring_size; int /*<<< orphan*/  oubring_base_l; int /*<<< orphan*/  inbring_base_l; int /*<<< orphan*/  oubring_base_h; int /*<<< orphan*/  inbring_base_h; } ;
struct TYPE_2__ {struct fsl_re_chan* private; struct dma_device* device; } ;
struct fsl_re_chan {int inb_phys_addr; int oub_phys_addr; void* inb_ring_virt_addr; struct fsl_re_drv_private* re_dev; struct fsl_re_chan_cfg* jrregs; void* oub_ring_virt_addr; int /*<<< orphan*/  free_q; int /*<<< orphan*/  submit_q; int /*<<< orphan*/  active_q; int /*<<< orphan*/  ack_q; int /*<<< orphan*/  desc_lock; struct device* dev; TYPE_1__ chan; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqtask; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FSL_RE_ADDR_BIT_MASK ; 
 int FSL_RE_ADDR_BIT_SHIFT ; 
 int FSL_RE_CFG1_CBS0 ; 
 int FSL_RE_CFG1_CBSI ; 
 int FSL_RE_ENABLE ; 
 int FSL_RE_REG_LIODN_MASK ; 
 int FSL_RE_RING_SIZE ; 
 int FSL_RE_RING_SIZE_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct fsl_re_drv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct fsl_re_chan*) ; 
 struct fsl_re_chan* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  fsl_re_dequeue ; 
 int /*<<< orphan*/  fsl_re_isr ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 struct platform_device* of_platform_device_create (struct device_node*,int /*<<< orphan*/ *,struct device*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fsl_re_chan_probe(struct platform_device *ofdev,
		      struct device_node *np, u8 q, u32 off)
{
	struct device *dev, *chandev;
	struct fsl_re_drv_private *re_priv;
	struct fsl_re_chan *chan;
	struct dma_device *dma_dev;
	u32 ptr;
	u32 status;
	int ret = 0, rc;
	struct platform_device *chan_ofdev;

	dev = &ofdev->dev;
	re_priv = dev_get_drvdata(dev);
	dma_dev = &re_priv->dma_dev;

	chan = devm_kzalloc(dev, sizeof(*chan), GFP_KERNEL);
	if (!chan)
		return -ENOMEM;

	/* create platform device for chan node */
	chan_ofdev = of_platform_device_create(np, NULL, dev);
	if (!chan_ofdev) {
		dev_err(dev, "Not able to create ofdev for jr %d\n", q);
		ret = -EINVAL;
		goto err_free;
	}

	/* read reg property from dts */
	rc = of_property_read_u32(np, "reg", &ptr);
	if (rc) {
		dev_err(dev, "Reg property not found in jr %d\n", q);
		ret = -ENODEV;
		goto err_free;
	}

	chan->jrregs = (struct fsl_re_chan_cfg *)((u8 *)re_priv->re_regs +
			off + ptr);

	/* read irq property from dts */
	chan->irq = irq_of_parse_and_map(np, 0);
	if (!chan->irq) {
		dev_err(dev, "No IRQ defined for JR %d\n", q);
		ret = -ENODEV;
		goto err_free;
	}

	snprintf(chan->name, sizeof(chan->name), "re_jr%02d", q);

	chandev = &chan_ofdev->dev;
	tasklet_init(&chan->irqtask, fsl_re_dequeue, (unsigned long)chandev);

	ret = request_irq(chan->irq, fsl_re_isr, 0, chan->name, chandev);
	if (ret) {
		dev_err(dev, "Unable to register interrupt for JR %d\n", q);
		ret = -EINVAL;
		goto err_free;
	}

	re_priv->re_jrs[q] = chan;
	chan->chan.device = dma_dev;
	chan->chan.private = chan;
	chan->dev = chandev;
	chan->re_dev = re_priv;

	spin_lock_init(&chan->desc_lock);
	INIT_LIST_HEAD(&chan->ack_q);
	INIT_LIST_HEAD(&chan->active_q);
	INIT_LIST_HEAD(&chan->submit_q);
	INIT_LIST_HEAD(&chan->free_q);

	chan->inb_ring_virt_addr = dma_pool_alloc(chan->re_dev->hw_desc_pool,
		GFP_KERNEL, &chan->inb_phys_addr);
	if (!chan->inb_ring_virt_addr) {
		dev_err(dev, "No dma memory for inb_ring_virt_addr\n");
		ret = -ENOMEM;
		goto err_free;
	}

	chan->oub_ring_virt_addr = dma_pool_alloc(chan->re_dev->hw_desc_pool,
		GFP_KERNEL, &chan->oub_phys_addr);
	if (!chan->oub_ring_virt_addr) {
		dev_err(dev, "No dma memory for oub_ring_virt_addr\n");
		ret = -ENOMEM;
		goto err_free_1;
	}

	/* Program the Inbound/Outbound ring base addresses and size */
	out_be32(&chan->jrregs->inbring_base_h,
		 chan->inb_phys_addr & FSL_RE_ADDR_BIT_MASK);
	out_be32(&chan->jrregs->oubring_base_h,
		 chan->oub_phys_addr & FSL_RE_ADDR_BIT_MASK);
	out_be32(&chan->jrregs->inbring_base_l,
		 chan->inb_phys_addr >> FSL_RE_ADDR_BIT_SHIFT);
	out_be32(&chan->jrregs->oubring_base_l,
		 chan->oub_phys_addr >> FSL_RE_ADDR_BIT_SHIFT);
	out_be32(&chan->jrregs->inbring_size,
		 FSL_RE_RING_SIZE << FSL_RE_RING_SIZE_SHIFT);
	out_be32(&chan->jrregs->oubring_size,
		 FSL_RE_RING_SIZE << FSL_RE_RING_SIZE_SHIFT);

	/* Read LIODN value from u-boot */
	status = in_be32(&chan->jrregs->jr_config_1) & FSL_RE_REG_LIODN_MASK;

	/* Program the CFG reg */
	out_be32(&chan->jrregs->jr_config_1,
		 FSL_RE_CFG1_CBSI | FSL_RE_CFG1_CBS0 | status);

	dev_set_drvdata(chandev, chan);

	/* Enable RE/CHAN */
	out_be32(&chan->jrregs->jr_command, FSL_RE_ENABLE);

	return 0;

err_free_1:
	dma_pool_free(chan->re_dev->hw_desc_pool, chan->inb_ring_virt_addr,
		      chan->inb_phys_addr);
err_free:
	return ret;
}