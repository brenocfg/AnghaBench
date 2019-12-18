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
typedef  int u32 ;
struct zynqmp_dma_chan {int idle; int err; int /*<<< orphan*/  dev; int /*<<< orphan*/  tasklet; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ZYNQMP_DMA_DONE ; 
 scalar_t__ ZYNQMP_DMA_IMR ; 
 int ZYNQMP_DMA_INT_DONE ; 
 int ZYNQMP_DMA_INT_ERR ; 
 int ZYNQMP_DMA_INT_OVRFL ; 
 scalar_t__ ZYNQMP_DMA_ISR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct zynqmp_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct zynqmp_dma_chan*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  zynqmp_dma_handle_ovfl_int (struct zynqmp_dma_chan*,int) ; 

__attribute__((used)) static irqreturn_t zynqmp_dma_irq_handler(int irq, void *data)
{
	struct zynqmp_dma_chan *chan = (struct zynqmp_dma_chan *)data;
	u32 isr, imr, status;
	irqreturn_t ret = IRQ_NONE;

	isr = readl(chan->regs + ZYNQMP_DMA_ISR);
	imr = readl(chan->regs + ZYNQMP_DMA_IMR);
	status = isr & ~imr;

	writel(isr, chan->regs + ZYNQMP_DMA_ISR);
	if (status & ZYNQMP_DMA_INT_DONE) {
		tasklet_schedule(&chan->tasklet);
		ret = IRQ_HANDLED;
	}

	if (status & ZYNQMP_DMA_DONE)
		chan->idle = true;

	if (status & ZYNQMP_DMA_INT_ERR) {
		chan->err = true;
		tasklet_schedule(&chan->tasklet);
		dev_err(chan->dev, "Channel %p has errors\n", chan);
		ret = IRQ_HANDLED;
	}

	if (status & ZYNQMP_DMA_INT_OVRFL) {
		zynqmp_dma_handle_ovfl_int(chan, status);
		dev_dbg(chan->dev, "Channel %p overflow interrupt\n", chan);
		ret = IRQ_HANDLED;
	}

	return ret;
}