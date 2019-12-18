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
struct dw_edma_chan {scalar_t__ status; scalar_t__ request; int /*<<< orphan*/  configured; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ EDMA_REQ_NONE ; 
 scalar_t__ EDMA_ST_BUSY ; 
 scalar_t__ EDMA_ST_PAUSE ; 
 int EPERM ; 
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  dw_edma_start_transfer (struct dw_edma_chan*) ; 

__attribute__((used)) static int dw_edma_device_resume(struct dma_chan *dchan)
{
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int err = 0;

	if (!chan->configured) {
		err = -EPERM;
	} else if (chan->status != EDMA_ST_PAUSE) {
		err = -EPERM;
	} else if (chan->request != EDMA_REQ_NONE) {
		err = -EPERM;
	} else {
		chan->status = EDMA_ST_BUSY;
		dw_edma_start_transfer(chan);
	}

	return err;
}