#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__ vchan; } ;
struct axi_dmac {TYPE_2__ chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AXI_DMAC_IRQ_EOT ; 
 unsigned int AXI_DMAC_IRQ_SOT ; 
 int /*<<< orphan*/  AXI_DMAC_REG_IRQ_PENDING ; 
 int /*<<< orphan*/  AXI_DMAC_REG_TRANSFER_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int axi_dmac_read (struct axi_dmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dmac_start_transfer (TYPE_2__*) ; 
 int axi_dmac_transfer_done (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  axi_dmac_write (struct axi_dmac*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t axi_dmac_interrupt_handler(int irq, void *devid)
{
	struct axi_dmac *dmac = devid;
	unsigned int pending;
	bool start_next = false;

	pending = axi_dmac_read(dmac, AXI_DMAC_REG_IRQ_PENDING);
	if (!pending)
		return IRQ_NONE;

	axi_dmac_write(dmac, AXI_DMAC_REG_IRQ_PENDING, pending);

	spin_lock(&dmac->chan.vchan.lock);
	/* One or more transfers have finished */
	if (pending & AXI_DMAC_IRQ_EOT) {
		unsigned int completed;

		completed = axi_dmac_read(dmac, AXI_DMAC_REG_TRANSFER_DONE);
		start_next = axi_dmac_transfer_done(&dmac->chan, completed);
	}
	/* Space has become available in the descriptor queue */
	if ((pending & AXI_DMAC_IRQ_SOT) || start_next)
		axi_dmac_start_transfer(&dmac->chan);
	spin_unlock(&dmac->chan.vchan.lock);

	return IRQ_HANDLED;
}