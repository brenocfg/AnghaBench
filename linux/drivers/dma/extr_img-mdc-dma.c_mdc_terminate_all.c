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
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct mdc_chan {TYPE_2__ vc; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDC_CONTROL_AND_STATUS ; 
 int /*<<< orphan*/  MDC_CONTROL_AND_STATUS_CANCEL ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  mdc_chan_writel (struct mdc_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdc_get_new_events (struct mdc_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdc_chan* to_mdc_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mdc_terminate_all(struct dma_chan *chan)
{
	struct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&mchan->vc.lock, flags);

	mdc_chan_writel(mchan, MDC_CONTROL_AND_STATUS_CANCEL,
			MDC_CONTROL_AND_STATUS);

	if (mchan->desc) {
		vchan_terminate_vdesc(&mchan->desc->vd);
		mchan->desc = NULL;
	}
	vchan_get_all_descriptors(&mchan->vc, &head);

	mdc_get_new_events(mchan);

	spin_unlock_irqrestore(&mchan->vc.lock, flags);

	vchan_dma_desc_free_list(&mchan->vc, &head);

	return 0;
}