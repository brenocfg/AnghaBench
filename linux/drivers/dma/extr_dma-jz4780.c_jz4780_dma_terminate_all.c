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
struct jz4780_dma_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct jz4780_dma_chan {TYPE_2__ vchan; int /*<<< orphan*/  id; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_DMA_REG_DCS ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  jz4780_dma_chan_disable (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 
 struct jz4780_dma_dev* jz4780_dma_chan_parent (struct jz4780_dma_chan*) ; 
 int /*<<< orphan*/  jz4780_dma_chn_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_terminate_vdesc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4780_dma_terminate_all(struct dma_chan *chan)
{
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	struct jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&jzchan->vchan.lock, flags);

	/* Clear the DMA status and stop the transfer. */
	jz4780_dma_chn_writel(jzdma, jzchan->id, JZ_DMA_REG_DCS, 0);
	if (jzchan->desc) {
		vchan_terminate_vdesc(&jzchan->desc->vdesc);
		jzchan->desc = NULL;
	}

	jz4780_dma_chan_disable(jzdma, jzchan->id);

	vchan_get_all_descriptors(&jzchan->vchan, &head);

	spin_unlock_irqrestore(&jzchan->vchan.lock, flags);

	vchan_dma_desc_free_list(&jzchan->vchan, &head);
	return 0;
}