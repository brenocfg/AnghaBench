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
typedef  int u32 ;
struct resource {int start; } ;
struct TYPE_3__ {int /*<<< orphan*/  channels; } ;
struct fsldma_device {int feature; scalar_t__ irq; int /*<<< orphan*/  dev; TYPE_1__ common; struct fsldma_chan** chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_node; TYPE_1__* device; } ;
struct fsldma_chan {int feature; int id; int idle; int /*<<< orphan*/  regs; scalar_t__ irq; TYPE_2__ common; int /*<<< orphan*/  pm_state; int /*<<< orphan*/  ld_completed; int /*<<< orphan*/  ld_running; int /*<<< orphan*/  ld_pending; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  set_request_count; int /*<<< orphan*/  set_dst_loop_size; int /*<<< orphan*/  set_src_loop_size; int /*<<< orphan*/  toggle_ext_start; int /*<<< orphan*/  toggle_ext_pause; int /*<<< orphan*/  name; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  FSL_DMA_IP_83XX 129 
#define  FSL_DMA_IP_85XX 128 
 int FSL_DMA_IP_MASK ; 
 int FSL_DMA_MAX_CHANS_PER_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char const*,scalar_t__) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_do_tasklet ; 
 int /*<<< orphan*/  dma_init (struct fsldma_chan*) ; 
 int /*<<< orphan*/  fsl_chan_set_dst_loop_size ; 
 int /*<<< orphan*/  fsl_chan_set_request_count ; 
 int /*<<< orphan*/  fsl_chan_set_src_loop_size ; 
 int /*<<< orphan*/  fsl_chan_toggle_ext_pause ; 
 int /*<<< orphan*/  fsl_chan_toggle_ext_start ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsldma_chan*) ; 
 struct fsldma_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cdar (struct fsldma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fsl_dma_chan_probe(struct fsldma_device *fdev,
	struct device_node *node, u32 feature, const char *compatible)
{
	struct fsldma_chan *chan;
	struct resource res;
	int err;

	/* alloc channel */
	chan = kzalloc(sizeof(*chan), GFP_KERNEL);
	if (!chan) {
		err = -ENOMEM;
		goto out_return;
	}

	/* ioremap registers for use */
	chan->regs = of_iomap(node, 0);
	if (!chan->regs) {
		dev_err(fdev->dev, "unable to ioremap registers\n");
		err = -ENOMEM;
		goto out_free_chan;
	}

	err = of_address_to_resource(node, 0, &res);
	if (err) {
		dev_err(fdev->dev, "unable to find 'reg' property\n");
		goto out_iounmap_regs;
	}

	chan->feature = feature;
	if (!fdev->feature)
		fdev->feature = chan->feature;

	/*
	 * If the DMA device's feature is different than the feature
	 * of its channels, report the bug
	 */
	WARN_ON(fdev->feature != chan->feature);

	chan->dev = fdev->dev;
	chan->id = (res.start & 0xfff) < 0x300 ?
		   ((res.start - 0x100) & 0xfff) >> 7 :
		   ((res.start - 0x200) & 0xfff) >> 7;
	if (chan->id >= FSL_DMA_MAX_CHANS_PER_DEVICE) {
		dev_err(fdev->dev, "too many channels for device\n");
		err = -EINVAL;
		goto out_iounmap_regs;
	}

	fdev->chan[chan->id] = chan;
	tasklet_init(&chan->tasklet, dma_do_tasklet, (unsigned long)chan);
	snprintf(chan->name, sizeof(chan->name), "chan%d", chan->id);

	/* Initialize the channel */
	dma_init(chan);

	/* Clear cdar registers */
	set_cdar(chan, 0);

	switch (chan->feature & FSL_DMA_IP_MASK) {
	case FSL_DMA_IP_85XX:
		chan->toggle_ext_pause = fsl_chan_toggle_ext_pause;
		/* Fall through */
	case FSL_DMA_IP_83XX:
		chan->toggle_ext_start = fsl_chan_toggle_ext_start;
		chan->set_src_loop_size = fsl_chan_set_src_loop_size;
		chan->set_dst_loop_size = fsl_chan_set_dst_loop_size;
		chan->set_request_count = fsl_chan_set_request_count;
	}

	spin_lock_init(&chan->desc_lock);
	INIT_LIST_HEAD(&chan->ld_pending);
	INIT_LIST_HEAD(&chan->ld_running);
	INIT_LIST_HEAD(&chan->ld_completed);
	chan->idle = true;
#ifdef CONFIG_PM
	chan->pm_state = RUNNING;
#endif

	chan->common.device = &fdev->common;
	dma_cookie_init(&chan->common);

	/* find the IRQ line, if it exists in the device tree */
	chan->irq = irq_of_parse_and_map(node, 0);

	/* Add the channel to DMA device channel list */
	list_add_tail(&chan->common.device_node, &fdev->common.channels);

	dev_info(fdev->dev, "#%d (%s), irq %d\n", chan->id, compatible,
		 chan->irq ? chan->irq : fdev->irq);

	return 0;

out_iounmap_regs:
	iounmap(chan->regs);
out_free_chan:
	kfree(chan);
out_return:
	return err;
}