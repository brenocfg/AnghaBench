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
struct hsu_dma_chan {TYPE_2__ vchan; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  hsu_dma_desc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hsu_dma_stop_channel (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hsu_dma_chan* to_hsu_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hsu_dma_terminate_all(struct dma_chan *chan)
{
	struct hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&hsuc->vchan.lock, flags);

	hsu_dma_stop_channel(hsuc);
	if (hsuc->desc) {
		hsu_dma_desc_free(&hsuc->desc->vdesc);
		hsuc->desc = NULL;
	}

	vchan_get_all_descriptors(&hsuc->vchan, &head);
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);
	vchan_dma_desc_free_list(&hsuc->vchan, &head);

	return 0;
}