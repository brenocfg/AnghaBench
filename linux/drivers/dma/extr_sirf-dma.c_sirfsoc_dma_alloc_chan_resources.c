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
struct TYPE_4__ {int /*<<< orphan*/  tx_submit; int /*<<< orphan*/  flags; } ;
struct sirfsoc_dma_desc {int /*<<< orphan*/  node; TYPE_2__ desc; } ;
struct sirfsoc_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct sirfsoc_dma {TYPE_1__ dma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int SIRFSOC_DMA_DESCRIPTORS ; 
 int /*<<< orphan*/  descs ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,struct dma_chan*) ; 
 struct sirfsoc_dma* dma_chan_to_sirfsoc_dma (struct dma_chan*) ; 
 struct sirfsoc_dma_chan* dma_chan_to_sirfsoc_dma_chan (struct dma_chan*) ; 
 struct sirfsoc_dma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_dma_tx_submit ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sirfsoc_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct sirfsoc_dma *sdma = dma_chan_to_sirfsoc_dma(chan);
	struct sirfsoc_dma_chan *schan = dma_chan_to_sirfsoc_dma_chan(chan);
	struct sirfsoc_dma_desc *sdesc;
	unsigned long flags;
	LIST_HEAD(descs);
	int i;

	pm_runtime_get_sync(sdma->dma.dev);

	/* Alloc descriptors for this channel */
	for (i = 0; i < SIRFSOC_DMA_DESCRIPTORS; i++) {
		sdesc = kzalloc(sizeof(*sdesc), GFP_KERNEL);
		if (!sdesc) {
			dev_notice(sdma->dma.dev, "Memory allocation error. "
				"Allocated only %u descriptors\n", i);
			break;
		}

		dma_async_tx_descriptor_init(&sdesc->desc, chan);
		sdesc->desc.flags = DMA_CTRL_ACK;
		sdesc->desc.tx_submit = sirfsoc_dma_tx_submit;

		list_add_tail(&sdesc->node, &descs);
	}

	/* Return error only if no descriptors were allocated */
	if (i == 0)
		return -ENOMEM;

	spin_lock_irqsave(&schan->lock, flags);

	list_splice_tail_init(&descs, &schan->free);
	spin_unlock_irqrestore(&schan->lock, flags);

	return i;
}