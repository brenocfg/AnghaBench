#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpc_dma_tcd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_submit; int /*<<< orphan*/  flags; } ;
struct mpc_dma_desc {int /*<<< orphan*/  node; void* tcd_paddr; struct mpc_dma_tcd* tcd; TYPE_3__ desc; } ;
struct mpc_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free; void* tcd_paddr; struct mpc_dma_tcd* tcd; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct mpc_dma {TYPE_2__* regs; TYPE_1__ dma; } ;
struct dma_chan {int /*<<< orphan*/  chan_id; } ;
typedef  void* dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dmaseei; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int MPC_DMA_DESCRIPTORS ; 
 int /*<<< orphan*/  descs ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int) ; 
 struct mpc_dma_tcd* dma_alloc_coherent (int /*<<< orphan*/ ,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_3__*,struct dma_chan*) ; 
 struct mpc_dma* dma_chan_to_mpc_dma (struct dma_chan*) ; 
 struct mpc_dma_chan* dma_chan_to_mpc_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct mpc_dma_tcd*,void*) ; 
 struct mpc_dma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc_dma_tx_submit ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpc_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	struct mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	struct mpc_dma_desc *mdesc;
	struct mpc_dma_tcd *tcd;
	dma_addr_t tcd_paddr;
	unsigned long flags;
	LIST_HEAD(descs);
	int i;

	/* Alloc DMA memory for Transfer Control Descriptors */
	tcd = dma_alloc_coherent(mdma->dma.dev,
			MPC_DMA_DESCRIPTORS * sizeof(struct mpc_dma_tcd),
							&tcd_paddr, GFP_KERNEL);
	if (!tcd)
		return -ENOMEM;

	/* Alloc descriptors for this channel */
	for (i = 0; i < MPC_DMA_DESCRIPTORS; i++) {
		mdesc = kzalloc(sizeof(struct mpc_dma_desc), GFP_KERNEL);
		if (!mdesc) {
			dev_notice(mdma->dma.dev,
				"Memory allocation error. Allocated only %u descriptors\n", i);
			break;
		}

		dma_async_tx_descriptor_init(&mdesc->desc, chan);
		mdesc->desc.flags = DMA_CTRL_ACK;
		mdesc->desc.tx_submit = mpc_dma_tx_submit;

		mdesc->tcd = &tcd[i];
		mdesc->tcd_paddr = tcd_paddr + (i * sizeof(struct mpc_dma_tcd));

		list_add_tail(&mdesc->node, &descs);
	}

	/* Return error only if no descriptors were allocated */
	if (i == 0) {
		dma_free_coherent(mdma->dma.dev,
			MPC_DMA_DESCRIPTORS * sizeof(struct mpc_dma_tcd),
								tcd, tcd_paddr);
		return -ENOMEM;
	}

	spin_lock_irqsave(&mchan->lock, flags);
	mchan->tcd = tcd;
	mchan->tcd_paddr = tcd_paddr;
	list_splice_tail_init(&descs, &mchan->free);
	spin_unlock_irqrestore(&mchan->lock, flags);

	/* Enable Error Interrupt */
	out_8(&mdma->regs->dmaseei, chan->chan_id);

	return 0;
}