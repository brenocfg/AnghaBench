#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct fsl_edma_chan {int /*<<< orphan*/ * tcd_pool; TYPE_1__ vchan; int /*<<< orphan*/ * edesc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_edma_chan_mux (struct fsl_edma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsl_edma_disable_request (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  fsl_edma_unprep_slave_dma (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_1__*,int /*<<< orphan*/ *) ; 

void fsl_edma_free_chan_resources(struct dma_chan *chan)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	unsigned long flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
	fsl_edma_disable_request(fsl_chan);
	fsl_edma_chan_mux(fsl_chan, 0, false);
	fsl_chan->edesc = NULL;
	vchan_get_all_descriptors(&fsl_chan->vchan, &head);
	fsl_edma_unprep_slave_dma(fsl_chan);
	spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);

	vchan_dma_desc_free_list(&fsl_chan->vchan, &head);
	dma_pool_destroy(fsl_chan->tcd_pool);
	fsl_chan->tcd_pool = NULL;
}