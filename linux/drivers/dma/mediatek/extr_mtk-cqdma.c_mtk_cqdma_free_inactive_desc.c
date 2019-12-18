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
struct virt_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_issued; int /*<<< orphan*/  desc_submitted; int /*<<< orphan*/  desc_allocated; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virt_dma_chan* to_virt_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (struct virt_dma_chan*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_cqdma_free_inactive_desc(struct dma_chan *c)
{
	struct virt_dma_chan *vc = to_virt_chan(c);
	unsigned long flags;
	LIST_HEAD(head);

	/*
	 * set desc_allocated, desc_submitted,
	 * and desc_issued as the candicates to be freed
	 */
	spin_lock_irqsave(&vc->lock, flags);
	list_splice_tail_init(&vc->desc_allocated, &head);
	list_splice_tail_init(&vc->desc_submitted, &head);
	list_splice_tail_init(&vc->desc_issued, &head);
	spin_unlock_irqrestore(&vc->lock, flags);

	/* free descriptor lists */
	vchan_dma_desc_free_list(vc, &head);
}