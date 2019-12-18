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
typedef  int u32 ;
struct txx9dmac_dev {int irq; struct txx9dmac_chan** chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct txx9dmac_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  chan; TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  MCR ; 
 int TXX9_DMA_CSR_ABCHC ; 
 int TXX9_DMA_CSR_NCHNC ; 
 int TXX9_DMA_CSR_NTRNFC ; 
 int TXX9_DMA_MAX_NR_CHANNELS ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int channel_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int dma_readl (struct txx9dmac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9dmac_scan_descriptors (struct txx9dmac_chan*) ; 

__attribute__((used)) static void txx9dmac_tasklet(unsigned long data)
{
	int irq;
	u32 csr;
	struct txx9dmac_chan *dc;

	struct txx9dmac_dev *ddev = (struct txx9dmac_dev *)data;
	u32 mcr;
	int i;

	mcr = dma_readl(ddev, MCR);
	dev_vdbg(ddev->chan[0]->dma.dev, "tasklet: mcr=%x\n", mcr);
	for (i = 0; i < TXX9_DMA_MAX_NR_CHANNELS; i++) {
		if ((mcr >> (24 + i)) & 0x11) {
			dc = ddev->chan[i];
			csr = channel_readl(dc, CSR);
			dev_vdbg(chan2dev(&dc->chan), "tasklet: status=%x\n",
				 csr);
			spin_lock(&dc->lock);
			if (csr & (TXX9_DMA_CSR_ABCHC | TXX9_DMA_CSR_NCHNC |
				   TXX9_DMA_CSR_NTRNFC))
				txx9dmac_scan_descriptors(dc);
			spin_unlock(&dc->lock);
		}
	}
	irq = ddev->irq;

	enable_irq(irq);
}