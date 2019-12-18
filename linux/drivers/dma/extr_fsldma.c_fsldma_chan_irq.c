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
struct fsldma_chan {int /*<<< orphan*/  tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FSL_DMA_SR_CB ; 
 int FSL_DMA_SR_CH ; 
 int FSL_DMA_SR_EOCDI ; 
 int FSL_DMA_SR_EOLNI ; 
 int FSL_DMA_SR_PE ; 
 int FSL_DMA_SR_TE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  chan_dbg (struct fsldma_chan*,char*,...) ; 
 int /*<<< orphan*/  chan_err (struct fsldma_chan*,char*,...) ; 
 int /*<<< orphan*/  dma_is_idle (struct fsldma_chan*) ; 
 scalar_t__ get_bcr (struct fsldma_chan*) ; 
 int get_sr (struct fsldma_chan*) ; 
 int /*<<< orphan*/  set_sr (struct fsldma_chan*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsldma_chan_irq(int irq, void *data)
{
	struct fsldma_chan *chan = data;
	u32 stat;

	/* save and clear the status register */
	stat = get_sr(chan);
	set_sr(chan, stat);
	chan_dbg(chan, "irq: stat = 0x%x\n", stat);

	/* check that this was really our device */
	stat &= ~(FSL_DMA_SR_CB | FSL_DMA_SR_CH);
	if (!stat)
		return IRQ_NONE;

	if (stat & FSL_DMA_SR_TE)
		chan_err(chan, "Transfer Error!\n");

	/*
	 * Programming Error
	 * The DMA_INTERRUPT async_tx is a NULL transfer, which will
	 * trigger a PE interrupt.
	 */
	if (stat & FSL_DMA_SR_PE) {
		chan_dbg(chan, "irq: Programming Error INT\n");
		stat &= ~FSL_DMA_SR_PE;
		if (get_bcr(chan) != 0)
			chan_err(chan, "Programming Error!\n");
	}

	/*
	 * For MPC8349, EOCDI event need to update cookie
	 * and start the next transfer if it exist.
	 */
	if (stat & FSL_DMA_SR_EOCDI) {
		chan_dbg(chan, "irq: End-of-Chain link INT\n");
		stat &= ~FSL_DMA_SR_EOCDI;
	}

	/*
	 * If it current transfer is the end-of-transfer,
	 * we should clear the Channel Start bit for
	 * prepare next transfer.
	 */
	if (stat & FSL_DMA_SR_EOLNI) {
		chan_dbg(chan, "irq: End-of-link INT\n");
		stat &= ~FSL_DMA_SR_EOLNI;
	}

	/* check that the DMA controller is really idle */
	if (!dma_is_idle(chan))
		chan_err(chan, "irq: controller not idle!\n");

	/* check that we handled all of the bits */
	if (stat)
		chan_err(chan, "irq: unhandled sr 0x%08x\n", stat);

	/*
	 * Schedule the tasklet to handle all cleanup of the current
	 * transaction. It will start a new transaction if there is
	 * one pending.
	 */
	tasklet_schedule(&chan->tasklet);
	chan_dbg(chan, "irq: Exit\n");
	return IRQ_HANDLED;
}