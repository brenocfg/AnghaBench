#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pata_pxa_data {int /*<<< orphan*/  dma_cookie; int /*<<< orphan*/  dma_chan; } ;
struct dma_async_tx_descriptor {struct pata_pxa_data* callback_param; int /*<<< orphan*/  callback; } ;
struct ata_queued_cmd {int flags; scalar_t__ dma_dir; int /*<<< orphan*/  dev; int /*<<< orphan*/  n_elem; int /*<<< orphan*/  sg; TYPE_1__* ap; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {struct pata_pxa_data* private_data; } ;

/* Variables and functions */
 int ATA_QCFLAG_DMAMAP ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ata_dev_err (int /*<<< orphan*/ ,char*) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  pxa_ata_dma_irq ; 

__attribute__((used)) static void pxa_qc_prep(struct ata_queued_cmd *qc)
{
	struct pata_pxa_data *pd = qc->ap->private_data;
	struct dma_async_tx_descriptor *tx;
	enum dma_transfer_direction dir;

	if (!(qc->flags & ATA_QCFLAG_DMAMAP))
		return;

	dir = (qc->dma_dir == DMA_TO_DEVICE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM);
	tx = dmaengine_prep_slave_sg(pd->dma_chan, qc->sg, qc->n_elem, dir,
				     DMA_PREP_INTERRUPT);
	if (!tx) {
		ata_dev_err(qc->dev, "prep_slave_sg() failed\n");
		return;
	}
	tx->callback = pxa_ata_dma_irq;
	tx->callback_param = pd;
	pd->dma_cookie = dmaengine_submit(tx);
}