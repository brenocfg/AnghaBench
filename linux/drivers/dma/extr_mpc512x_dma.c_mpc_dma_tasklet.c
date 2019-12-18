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
typedef  int uint ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mpc_dma {int error_status; TYPE_1__ dma; int /*<<< orphan*/  error_status_lock; } ;

/* Variables and functions */
 int MPC_DMA_DMAES_CPE ; 
 int MPC_DMA_DMAES_DAE ; 
 int MPC_DMA_DMAES_DBE ; 
 int MPC_DMA_DMAES_DOE ; 
 int /*<<< orphan*/  MPC_DMA_DMAES_ERRCHN (int) ; 
 int MPC_DMA_DMAES_GPE ; 
 int MPC_DMA_DMAES_NCE ; 
 int MPC_DMA_DMAES_SAE ; 
 int MPC_DMA_DMAES_SBE ; 
 int MPC_DMA_DMAES_SGE ; 
 int MPC_DMA_DMAES_SOE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpc_dma_process_completed (struct mpc_dma*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpc_dma_tasklet(unsigned long data)
{
	struct mpc_dma *mdma = (void *)data;
	unsigned long flags;
	uint es;

	spin_lock_irqsave(&mdma->error_status_lock, flags);
	es = mdma->error_status;
	mdma->error_status = 0;
	spin_unlock_irqrestore(&mdma->error_status_lock, flags);

	/* Print nice error report */
	if (es) {
		dev_err(mdma->dma.dev,
			"Hardware reported following error(s) on channel %u:\n",
						      MPC_DMA_DMAES_ERRCHN(es));

		if (es & MPC_DMA_DMAES_GPE)
			dev_err(mdma->dma.dev, "- Group Priority Error\n");
		if (es & MPC_DMA_DMAES_CPE)
			dev_err(mdma->dma.dev, "- Channel Priority Error\n");
		if (es & MPC_DMA_DMAES_SAE)
			dev_err(mdma->dma.dev, "- Source Address Error\n");
		if (es & MPC_DMA_DMAES_SOE)
			dev_err(mdma->dma.dev, "- Source Offset Configuration Error\n");
		if (es & MPC_DMA_DMAES_DAE)
			dev_err(mdma->dma.dev, "- Destination Address Error\n");
		if (es & MPC_DMA_DMAES_DOE)
			dev_err(mdma->dma.dev, "- Destination Offset Configuration Error\n");
		if (es & MPC_DMA_DMAES_NCE)
			dev_err(mdma->dma.dev, "- NBytes/Citter Configuration Error\n");
		if (es & MPC_DMA_DMAES_SGE)
			dev_err(mdma->dma.dev, "- Scatter/Gather Configuration Error\n");
		if (es & MPC_DMA_DMAES_SBE)
			dev_err(mdma->dma.dev, "- Source Bus Error\n");
		if (es & MPC_DMA_DMAES_DBE)
			dev_err(mdma->dma.dev, "- Destination Bus Error\n");
	}

	mpc_dma_process_completed(mdma);
}