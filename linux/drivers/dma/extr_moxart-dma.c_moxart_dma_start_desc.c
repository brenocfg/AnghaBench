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
struct virt_dma_desc {int /*<<< orphan*/  tx; int /*<<< orphan*/  node; } ;
struct moxart_chan {scalar_t__ sgidx; int /*<<< orphan*/ * desc; int /*<<< orphan*/  vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  moxart_dma_start_sg (struct moxart_chan*,int /*<<< orphan*/ ) ; 
 struct moxart_chan* to_moxart_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/ * to_moxart_dma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moxart_dma_start_desc(struct dma_chan *chan)
{
	struct moxart_chan *ch = to_moxart_dma_chan(chan);
	struct virt_dma_desc *vd;

	vd = vchan_next_desc(&ch->vc);

	if (!vd) {
		ch->desc = NULL;
		return;
	}

	list_del(&vd->node);

	ch->desc = to_moxart_dma_desc(&vd->tx);
	ch->sgidx = 0;

	moxart_dma_start_sg(ch, 0);
}