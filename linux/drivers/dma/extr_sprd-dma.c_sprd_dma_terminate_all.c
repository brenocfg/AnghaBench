#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct sprd_dma_chn {TYPE_2__ vc; TYPE_1__* cur_desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {struct virt_dma_desc vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprd_dma_free_desc (struct virt_dma_desc*) ; 
 int /*<<< orphan*/  sprd_dma_stop (struct sprd_dma_chn*) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_dma_terminate_all(struct dma_chan *chan)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	struct virt_dma_desc *cur_vd = NULL;
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&schan->vc.lock, flags);
	if (schan->cur_desc)
		cur_vd = &schan->cur_desc->vd;

	sprd_dma_stop(schan);

	vchan_get_all_descriptors(&schan->vc, &head);
	spin_unlock_irqrestore(&schan->vc.lock, flags);

	if (cur_vd)
		sprd_dma_free_desc(cur_vd);

	vchan_dma_desc_free_list(&schan->vc, &head);
	return 0;
}