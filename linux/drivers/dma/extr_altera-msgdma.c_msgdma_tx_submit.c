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
struct msgdma_sw_desc {int /*<<< orphan*/  node; } ;
struct msgdma_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_list; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct msgdma_device* to_mdev (int /*<<< orphan*/ ) ; 
 struct msgdma_sw_desc* tx_to_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t msgdma_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct msgdma_device *mdev = to_mdev(tx->chan);
	struct msgdma_sw_desc *new;
	dma_cookie_t cookie;
	unsigned long flags;

	new = tx_to_desc(tx);
	spin_lock_irqsave(&mdev->lock, flags);
	cookie = dma_cookie_assign(tx);

	list_add_tail(&new->node, &mdev->pending_list);
	spin_unlock_irqrestore(&mdev->lock, flags);

	return cookie;
}