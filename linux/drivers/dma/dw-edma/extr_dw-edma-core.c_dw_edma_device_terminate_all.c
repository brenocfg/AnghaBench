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
struct dw_edma_chan {int configured; scalar_t__ status; scalar_t__ request; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_COMPLETE ; 
 scalar_t__ EDMA_REQ_PAUSE ; 
 scalar_t__ EDMA_REQ_STOP ; 
 scalar_t__ EDMA_ST_IDLE ; 
 scalar_t__ EDMA_ST_PAUSE ; 
 int EPERM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 scalar_t__ dw_edma_v0_core_ch_status (struct dw_edma_chan*) ; 
 int /*<<< orphan*/  head ; 

__attribute__((used)) static int dw_edma_device_terminate_all(struct dma_chan *dchan)
{
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int err = 0;
	LIST_HEAD(head);

	if (!chan->configured) {
		/* Do nothing */
	} else if (chan->status == EDMA_ST_PAUSE) {
		chan->status = EDMA_ST_IDLE;
		chan->configured = false;
	} else if (chan->status == EDMA_ST_IDLE) {
		chan->configured = false;
	} else if (dw_edma_v0_core_ch_status(chan) == DMA_COMPLETE) {
		/*
		 * The channel is in a false BUSY state, probably didn't
		 * receive or lost an interrupt
		 */
		chan->status = EDMA_ST_IDLE;
		chan->configured = false;
	} else if (chan->request > EDMA_REQ_PAUSE) {
		err = -EPERM;
	} else {
		chan->request = EDMA_REQ_STOP;
	}

	return err;
}