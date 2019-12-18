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
struct owl_dma_vchan {TYPE_2__ vc; TYPE_1__* txd; scalar_t__ pchan; } ;
struct owl_dma {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  owl_dma_desc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  owl_dma_phy_free (struct owl_dma*,struct owl_dma_vchan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct owl_dma* to_owl_dma (int /*<<< orphan*/ ) ; 
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int owl_dma_terminate_all(struct dma_chan *chan)
{
	struct owl_dma *od = to_owl_dma(chan->device);
	struct owl_dma_vchan *vchan = to_owl_vchan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	if (vchan->pchan)
		owl_dma_phy_free(od, vchan);

	if (vchan->txd) {
		owl_dma_desc_free(&vchan->txd->vd);
		vchan->txd = NULL;
	}

	vchan_get_all_descriptors(&vchan->vc, &head);
	vchan_dma_desc_free_list(&vchan->vc, &head);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	return 0;
}