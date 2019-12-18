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
struct iop_adma_chan {scalar_t__ pending; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iop_chan_append (struct iop_adma_chan*) ; 
 struct iop_adma_chan* to_iop_adma_chan (struct dma_chan*) ; 

__attribute__((used)) static void iop_adma_issue_pending(struct dma_chan *chan)
{
	struct iop_adma_chan *iop_chan = to_iop_adma_chan(chan);

	if (iop_chan->pending) {
		iop_chan->pending = 0;
		iop_chan_append(iop_chan);
	}
}