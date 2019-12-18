#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct edma_regs {int /*<<< orphan*/  cint; int /*<<< orphan*/  intl; int /*<<< orphan*/  inth; } ;
struct fsl_edma_engine {unsigned int n_chans; struct fsl_edma_chan* chans; struct edma_regs regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct fsl_edma_chan {int idle; TYPE_2__ vchan; TYPE_1__* edesc; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_3__ vdesc; int /*<<< orphan*/  iscyclic; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int /*<<< orphan*/  EDMA_MASK_CH (unsigned int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  fsl_edma_xfer_desc (struct fsl_edma_chan*) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_3__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_3__*) ; 

__attribute__((used)) static irqreturn_t mcf_edma_tx_handler(int irq, void *dev_id)
{
	struct fsl_edma_engine *mcf_edma = dev_id;
	struct edma_regs *regs = &mcf_edma->regs;
	unsigned int ch;
	struct fsl_edma_chan *mcf_chan;
	u64 intmap;

	intmap = ioread32(regs->inth);
	intmap <<= 32;
	intmap |= ioread32(regs->intl);
	if (!intmap)
		return IRQ_NONE;

	for (ch = 0; ch < mcf_edma->n_chans; ch++) {
		if (intmap & BIT(ch)) {
			iowrite8(EDMA_MASK_CH(ch), regs->cint);

			mcf_chan = &mcf_edma->chans[ch];

			spin_lock(&mcf_chan->vchan.lock);
			if (!mcf_chan->edesc->iscyclic) {
				list_del(&mcf_chan->edesc->vdesc.node);
				vchan_cookie_complete(&mcf_chan->edesc->vdesc);
				mcf_chan->edesc = NULL;
				mcf_chan->status = DMA_COMPLETE;
				mcf_chan->idle = true;
			} else {
				vchan_cyclic_callback(&mcf_chan->edesc->vdesc);
			}

			if (!mcf_chan->edesc)
				fsl_edma_xfer_desc(mcf_chan);

			spin_unlock(&mcf_chan->vchan.lock);
		}
	}

	return IRQ_HANDLED;
}