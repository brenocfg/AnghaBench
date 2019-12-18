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
struct xilinx_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* start_transfer ) (struct xilinx_dma_chan*) ;} ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xilinx_dma_chan*) ; 
 struct xilinx_dma_chan* to_xilinx_chan (struct dma_chan*) ; 

__attribute__((used)) static void xilinx_dma_issue_pending(struct dma_chan *dchan)
{
	struct xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	unsigned long flags;

	spin_lock_irqsave(&chan->lock, flags);
	chan->start_transfer(chan);
	spin_unlock_irqrestore(&chan->lock, flags);
}