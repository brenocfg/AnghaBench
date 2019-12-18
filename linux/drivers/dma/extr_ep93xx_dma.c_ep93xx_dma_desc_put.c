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
struct ep93xx_dma_desc {int /*<<< orphan*/  node; int /*<<< orphan*/  tx_list; } ;
struct ep93xx_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ep93xx_dma_desc_put(struct ep93xx_dma_chan *edmac,
				struct ep93xx_dma_desc *desc)
{
	if (desc) {
		unsigned long flags;

		spin_lock_irqsave(&edmac->lock, flags);
		list_splice_init(&desc->tx_list, &edmac->free_list);
		list_add(&desc->node, &edmac->free_list);
		spin_unlock_irqrestore(&edmac->lock, flags);
	}
}