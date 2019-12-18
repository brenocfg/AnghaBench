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
struct tegra_dma_desc {int /*<<< orphan*/  node; int /*<<< orphan*/  tx_list; } ;
struct tegra_dma_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_dma_desc; int /*<<< orphan*/  free_sg_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tegra_dma_desc_put(struct tegra_dma_channel *tdc,
		struct tegra_dma_desc *dma_desc)
{
	unsigned long flags;

	spin_lock_irqsave(&tdc->lock, flags);
	if (!list_empty(&dma_desc->tx_list))
		list_splice_init(&dma_desc->tx_list, &tdc->free_sg_req);
	list_add_tail(&dma_desc->node, &tdc->free_dma_desc);
	spin_unlock_irqrestore(&tdc->lock, flags);
}