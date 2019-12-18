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
typedef  int uint32_t ;
struct xdma_sglist {scalar_t__ direction; int first; int last; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; scalar_t__ len; } ;
struct xdma_channel {scalar_t__ chan; } ;
struct softdma_softc {int dummy; } ;
struct softdma_desc {int src_incr; int dst_incr; scalar_t__ direction; int len; int /*<<< orphan*/  control; scalar_t__ reserved; scalar_t__ status; scalar_t__ transfered; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct softdma_channel {size_t idx_head; int run; int /*<<< orphan*/  descs_used_count; struct softdma_desc* descs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_INT_ENABLE ; 
 int /*<<< orphan*/  CONTROL_GEN_EOP ; 
 int /*<<< orphan*/  CONTROL_GEN_SOP ; 
 int /*<<< orphan*/  CONTROL_OWN ; 
 int /*<<< orphan*/  SOFTDMA_RX_EVENTS ; 
 scalar_t__ XDMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 struct softdma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softdma_memc_write (struct softdma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int softdma_next_desc (struct softdma_channel*,int) ; 
 int /*<<< orphan*/  wakeup (struct softdma_channel*) ; 

__attribute__((used)) static int
softdma_channel_submit_sg(device_t dev, struct xdma_channel *xchan,
    struct xdma_sglist *sg, uint32_t sg_n)
{
	struct softdma_channel *chan;
	struct softdma_desc *desc;
	struct softdma_softc *sc;
	uint32_t enqueued;
	uint32_t saved_dir;
	uint32_t tmp;
	uint32_t len;
	int i;

	sc = device_get_softc(dev);

	chan = (struct softdma_channel *)xchan->chan;

	enqueued = 0;

	for (i = 0; i < sg_n; i++) {
		len = (uint32_t)sg[i].len;

		desc = &chan->descs[chan->idx_head];
		desc->src_addr = sg[i].src_addr;
		desc->dst_addr = sg[i].dst_addr;
		if (sg[i].direction == XDMA_MEM_TO_DEV) {
			desc->src_incr = 1;
			desc->dst_incr = 0;
		} else {
			desc->src_incr = 0;
			desc->dst_incr = 1;
		}
		desc->direction = sg[i].direction;
		saved_dir = sg[i].direction;
		desc->len = len;
		desc->transfered = 0;
		desc->status = 0;
		desc->reserved = 0;
		desc->control = 0;

		if (sg[i].first == 1)
			desc->control |= CONTROL_GEN_SOP;
		if (sg[i].last == 1)
			desc->control |= CONTROL_GEN_EOP;

		tmp = chan->idx_head;
		chan->idx_head = softdma_next_desc(chan, chan->idx_head);
		atomic_add_int(&chan->descs_used_count, 1);
		desc->control |= CONTROL_OWN;
		enqueued += 1;
	}

	if (enqueued == 0)
		return (0);

	if (saved_dir == XDMA_MEM_TO_DEV) {
		chan->run = 1;
		wakeup(chan);
	} else
		softdma_memc_write(sc,
		    A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_INT_ENABLE,
		    SOFTDMA_RX_EVENTS);

	return (0);
}