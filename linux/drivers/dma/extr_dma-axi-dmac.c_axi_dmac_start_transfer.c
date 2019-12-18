#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct axi_dmac_sg {int schedule_when_free; int dest_addr; int dest_stride; int src_addr; int src_stride; int x_len; int y_len; void* id; } ;
struct TYPE_3__ {int /*<<< orphan*/  callback; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct axi_dmac_desc {size_t num_submitted; int num_sgs; TYPE_2__ vdesc; scalar_t__ cyclic; scalar_t__ have_partial_xfer; struct axi_dmac_sg* sg; } ;
struct axi_dmac_chan {scalar_t__ hw_partial_xfer; scalar_t__ hw_cyclic; struct axi_dmac_desc* next_desc; int /*<<< orphan*/  active_descs; int /*<<< orphan*/  vchan; } ;
struct axi_dmac {int dummy; } ;

/* Variables and functions */
 unsigned int AXI_DMAC_FLAG_CYCLIC ; 
 unsigned int AXI_DMAC_FLAG_LAST ; 
 unsigned int AXI_DMAC_FLAG_PARTIAL_REPORT ; 
 int /*<<< orphan*/  AXI_DMAC_REG_DEST_ADDRESS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_DEST_STRIDE ; 
 int /*<<< orphan*/  AXI_DMAC_REG_FLAGS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_SRC_ADDRESS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_SRC_STRIDE ; 
 int /*<<< orphan*/  AXI_DMAC_REG_START_TRANSFER ; 
 int /*<<< orphan*/  AXI_DMAC_REG_TRANSFER_ID ; 
 int /*<<< orphan*/  AXI_DMAC_REG_X_LENGTH ; 
 int /*<<< orphan*/  AXI_DMAC_REG_Y_LENGTH ; 
 void* AXI_DMAC_SG_UNUSED ; 
 scalar_t__ axi_dmac_dest_is_mem (struct axi_dmac_chan*) ; 
 void* axi_dmac_read (struct axi_dmac*,int /*<<< orphan*/ ) ; 
 scalar_t__ axi_dmac_src_is_mem (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  axi_dmac_write (struct axi_dmac*,int /*<<< orphan*/ ,int) ; 
 struct axi_dmac* chan_to_axi_dmac (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct axi_dmac_desc* to_axi_dmac_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void axi_dmac_start_transfer(struct axi_dmac_chan *chan)
{
	struct axi_dmac *dmac = chan_to_axi_dmac(chan);
	struct virt_dma_desc *vdesc;
	struct axi_dmac_desc *desc;
	struct axi_dmac_sg *sg;
	unsigned int flags = 0;
	unsigned int val;

	val = axi_dmac_read(dmac, AXI_DMAC_REG_START_TRANSFER);
	if (val) /* Queue is full, wait for the next SOT IRQ */
		return;

	desc = chan->next_desc;

	if (!desc) {
		vdesc = vchan_next_desc(&chan->vchan);
		if (!vdesc)
			return;
		list_move_tail(&vdesc->node, &chan->active_descs);
		desc = to_axi_dmac_desc(vdesc);
	}
	sg = &desc->sg[desc->num_submitted];

	/* Already queued in cyclic mode. Wait for it to finish */
	if (sg->id != AXI_DMAC_SG_UNUSED) {
		sg->schedule_when_free = true;
		return;
	}

	desc->num_submitted++;
	if (desc->num_submitted == desc->num_sgs ||
	    desc->have_partial_xfer) {
		if (desc->cyclic)
			desc->num_submitted = 0; /* Start again */
		else
			chan->next_desc = NULL;
		flags |= AXI_DMAC_FLAG_LAST;
	} else {
		chan->next_desc = desc;
	}

	sg->id = axi_dmac_read(dmac, AXI_DMAC_REG_TRANSFER_ID);

	if (axi_dmac_dest_is_mem(chan)) {
		axi_dmac_write(dmac, AXI_DMAC_REG_DEST_ADDRESS, sg->dest_addr);
		axi_dmac_write(dmac, AXI_DMAC_REG_DEST_STRIDE, sg->dest_stride);
	}

	if (axi_dmac_src_is_mem(chan)) {
		axi_dmac_write(dmac, AXI_DMAC_REG_SRC_ADDRESS, sg->src_addr);
		axi_dmac_write(dmac, AXI_DMAC_REG_SRC_STRIDE, sg->src_stride);
	}

	/*
	 * If the hardware supports cyclic transfers and there is no callback to
	 * call and only a single segment, enable hw cyclic mode to avoid
	 * unnecessary interrupts.
	 */
	if (chan->hw_cyclic && desc->cyclic && !desc->vdesc.tx.callback &&
		desc->num_sgs == 1)
		flags |= AXI_DMAC_FLAG_CYCLIC;

	if (chan->hw_partial_xfer)
		flags |= AXI_DMAC_FLAG_PARTIAL_REPORT;

	axi_dmac_write(dmac, AXI_DMAC_REG_X_LENGTH, sg->x_len - 1);
	axi_dmac_write(dmac, AXI_DMAC_REG_Y_LENGTH, sg->y_len - 1);
	axi_dmac_write(dmac, AXI_DMAC_REG_FLAGS, flags);
	axi_dmac_write(dmac, AXI_DMAC_REG_START_TRANSFER, 1);
}