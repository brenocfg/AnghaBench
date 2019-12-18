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
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct axi_dmac_chan {TYPE_1__ vchan; } ;
struct axi_dmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_DMAC_CTRL_ENABLE ; 
 int /*<<< orphan*/  AXI_DMAC_REG_CTRL ; 
 int /*<<< orphan*/  axi_dmac_start_transfer (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  axi_dmac_write (struct axi_dmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axi_dmac* chan_to_axi_dmac (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void axi_dmac_issue_pending(struct dma_chan *c)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	struct axi_dmac *dmac = chan_to_axi_dmac(chan);
	unsigned long flags;

	axi_dmac_write(dmac, AXI_DMAC_REG_CTRL, AXI_DMAC_CTRL_ENABLE);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	if (vchan_issue_pending(&chan->vchan))
		axi_dmac_start_transfer(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
}