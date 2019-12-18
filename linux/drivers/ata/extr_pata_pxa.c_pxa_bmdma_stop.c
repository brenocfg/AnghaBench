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
struct pata_pxa_data {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  dma_cookie; } ;
struct ata_queued_cmd {int /*<<< orphan*/  dev; TYPE_1__* ap; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
struct TYPE_2__ {struct pata_pxa_data* private_data; } ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int DMA_ERROR ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  ata_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa_bmdma_stop(struct ata_queued_cmd *qc)
{
	struct pata_pxa_data *pd = qc->ap->private_data;
	enum dma_status status;

	status = dmaengine_tx_status(pd->dma_chan, pd->dma_cookie, NULL);
	if (status != DMA_ERROR && status != DMA_COMPLETE &&
	    wait_for_completion_timeout(&pd->dma_done, HZ))
		ata_dev_err(qc->dev, "Timeout waiting for DMA completion!");

	dmaengine_terminate_all(pd->dma_chan);
}