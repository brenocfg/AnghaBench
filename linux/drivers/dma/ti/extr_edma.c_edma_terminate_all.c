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
struct edma_chan {TYPE_2__ vchan; TYPE_1__* edesc; int /*<<< orphan*/  tc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdesc; scalar_t__ cyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTQ_DEFAULT ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_assign_channel_eventq (struct edma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int edma_terminate_all(struct dma_chan *chan)
{
	struct edma_chan *echan = to_edma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&echan->vchan.lock, flags);

	/*
	 * Stop DMA activity: we assume the callback will not be called
	 * after edma_dma() returns (even if it does, it will see
	 * echan->edesc is NULL and exit.)
	 */
	if (echan->edesc) {
		edma_stop(echan);
		/* Move the cyclic channel back to default queue */
		if (!echan->tc && echan->edesc->cyclic)
			edma_assign_channel_eventq(echan, EVENTQ_DEFAULT);

		vchan_terminate_vdesc(&echan->edesc->vdesc);
		echan->edesc = NULL;
	}

	vchan_get_all_descriptors(&echan->vchan, &head);
	spin_unlock_irqrestore(&echan->vchan.lock, flags);
	vchan_dma_desc_free_list(&echan->vchan, &head);

	return 0;
}