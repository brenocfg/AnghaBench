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
struct imxdma_engine {int /*<<< orphan*/  lock; } ;
struct imxdma_channel {int /*<<< orphan*/  ld_free; int /*<<< orphan*/  ld_queue; int /*<<< orphan*/  ld_active; struct imxdma_engine* imxdma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  imxdma_disable_hw (struct imxdma_channel*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct imxdma_channel* to_imxdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int imxdma_terminate_all(struct dma_chan *chan)
{
	struct imxdma_channel *imxdmac = to_imxdma_chan(chan);
	struct imxdma_engine *imxdma = imxdmac->imxdma;
	unsigned long flags;

	imxdma_disable_hw(imxdmac);

	spin_lock_irqsave(&imxdma->lock, flags);
	list_splice_tail_init(&imxdmac->ld_active, &imxdmac->ld_free);
	list_splice_tail_init(&imxdmac->ld_queue, &imxdmac->ld_free);
	spin_unlock_irqrestore(&imxdma->lock, flags);
	return 0;
}