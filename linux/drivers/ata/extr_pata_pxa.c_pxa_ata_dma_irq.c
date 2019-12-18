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
struct pata_pxa_data {int /*<<< orphan*/  dma_done; int /*<<< orphan*/  dma_cookie; int /*<<< orphan*/  dma_chan; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int DMA_ERROR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_ata_dma_irq(void *d)
{
	struct pata_pxa_data *pd = d;
	enum dma_status status;

	status = dmaengine_tx_status(pd->dma_chan, pd->dma_cookie, NULL);
	if (status == DMA_ERROR || status == DMA_COMPLETE)
		complete(&pd->dma_done);
}