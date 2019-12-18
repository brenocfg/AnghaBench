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
struct imxdma_engine {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct imxdma_channel {int /*<<< orphan*/  ld_queue; TYPE_1__ ld_free; struct imxdma_engine* imxdma; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct imxdma_channel* to_imxdma_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_cookie_t imxdma_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct imxdma_channel *imxdmac = to_imxdma_chan(tx->chan);
	struct imxdma_engine *imxdma = imxdmac->imxdma;
	dma_cookie_t cookie;
	unsigned long flags;

	spin_lock_irqsave(&imxdma->lock, flags);
	list_move_tail(imxdmac->ld_free.next, &imxdmac->ld_queue);
	cookie = dma_cookie_assign(tx);
	spin_unlock_irqrestore(&imxdma->lock, flags);

	return cookie;
}