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
struct ioatdma_chan {int /*<<< orphan*/  head; int /*<<< orphan*/  state; } ;
struct dma_async_tx_descriptor {unsigned long flags; } ;
struct ioat_ring_ent {int len; struct dma_async_tx_descriptor txd; struct ioat_dma_descriptor* hw; } ;
struct TYPE_2__ {int null; int int_en; int fence; int compl_write; } ;
struct ioat_dma_descriptor {scalar_t__ dst_addr; scalar_t__ src_addr; int /*<<< orphan*/  size; TYPE_1__ ctl_f; scalar_t__ ctl; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 unsigned long DMA_PREP_FENCE ; 
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 int /*<<< orphan*/  NULL_DESC_BUFFER_SIZE ; 
 int /*<<< orphan*/  dump_desc_dbg (struct ioatdma_chan*,struct ioat_ring_ent*) ; 
 scalar_t__ ioat_check_space_lock (struct ioatdma_chan*,int) ; 
 struct ioat_ring_ent* ioat_get_ring_ent (struct ioatdma_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 

struct dma_async_tx_descriptor *
ioat_prep_interrupt_lock(struct dma_chan *c, unsigned long flags)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	struct ioat_ring_ent *desc;
	struct ioat_dma_descriptor *hw;

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		return NULL;

	if (ioat_check_space_lock(ioat_chan, 1) == 0)
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->head);
	else
		return NULL;

	hw = desc->hw;
	hw->ctl = 0;
	hw->ctl_f.null = 1;
	hw->ctl_f.int_en = 1;
	hw->ctl_f.fence = !!(flags & DMA_PREP_FENCE);
	hw->ctl_f.compl_write = 1;
	hw->size = NULL_DESC_BUFFER_SIZE;
	hw->src_addr = 0;
	hw->dst_addr = 0;

	desc->txd.flags = flags;
	desc->len = 1;

	dump_desc_dbg(ioat_chan, desc);

	/* we leave the channel locked to ensure in order submission */
	return &desc->txd;
}