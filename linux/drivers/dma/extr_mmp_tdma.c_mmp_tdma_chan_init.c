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
struct TYPE_4__ {int /*<<< orphan*/  channels; } ;
struct mmp_tdma_device {TYPE_2__ device; struct mmp_tdma_chan** tdmac; scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct mmp_tdma_chan {int irq; int idx; int type; TYPE_1__ chan; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  status; struct gen_pool* pool; scalar_t__ reg_base; int /*<<< orphan*/  dev; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TDMA_CHANNEL_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mmp_tdma_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_do_tasklet ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int mmp_tdma_chan_init(struct mmp_tdma_device *tdev,
					int idx, int irq,
					int type, struct gen_pool *pool)
{
	struct mmp_tdma_chan *tdmac;

	if (idx >= TDMA_CHANNEL_NUM) {
		dev_err(tdev->dev, "too many channels for device!\n");
		return -EINVAL;
	}

	/* alloc channel */
	tdmac = devm_kzalloc(tdev->dev, sizeof(*tdmac), GFP_KERNEL);
	if (!tdmac)
		return -ENOMEM;

	if (irq)
		tdmac->irq = irq;
	tdmac->dev	   = tdev->dev;
	tdmac->chan.device = &tdev->device;
	tdmac->idx	   = idx;
	tdmac->type	   = type;
	tdmac->reg_base	   = tdev->base + idx * 4;
	tdmac->pool	   = pool;
	tdmac->status = DMA_COMPLETE;
	tdev->tdmac[tdmac->idx] = tdmac;
	tasklet_init(&tdmac->tasklet, dma_do_tasklet, (unsigned long)tdmac);

	/* add the channel to tdma_chan list */
	list_add_tail(&tdmac->chan.device_node,
			&tdev->device.channels);
	return 0;
}