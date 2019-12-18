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
struct dma_slave_config {int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr_width; } ;
struct dma_chan {struct at_dma_slave* private; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  cookie; int /*<<< orphan*/  phys; } ;
struct at_dma_slave {int dummy; } ;
struct at_dma_chan {int /*<<< orphan*/  status; struct dma_slave_config dma_sconfig; } ;
struct TYPE_2__ {int /*<<< orphan*/  dscr; } ;
struct at_desc {size_t total_len; struct dma_async_tx_descriptor txd; TYPE_1__ lli; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATC_IS_CYCLIC ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  atc_desc_chain (struct at_desc**,struct at_desc**,struct at_desc*) ; 
 struct at_desc* atc_desc_get (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_desc_put (struct at_dma_chan*,struct at_desc*) ; 
 scalar_t__ atc_dma_cyclic_check_values (unsigned int,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ atc_dma_cyclic_fill_desc (struct dma_chan*,struct at_desc*,unsigned int,int /*<<< orphan*/ ,unsigned int,size_t,int) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int convert_buswidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 
 unsigned long test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct at_dma_chan* to_at_dma_chan (struct dma_chan*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
atc_prep_dma_cyclic(struct dma_chan *chan, dma_addr_t buf_addr, size_t buf_len,
		size_t period_len, enum dma_transfer_direction direction,
		unsigned long flags)
{
	struct at_dma_chan	*atchan = to_at_dma_chan(chan);
	struct at_dma_slave	*atslave = chan->private;
	struct dma_slave_config	*sconfig = &atchan->dma_sconfig;
	struct at_desc		*first = NULL;
	struct at_desc		*prev = NULL;
	unsigned long		was_cyclic;
	unsigned int		reg_width;
	unsigned int		periods = buf_len / period_len;
	unsigned int		i;

	dev_vdbg(chan2dev(chan), "prep_dma_cyclic: %s buf@%pad - %d (%d/%d)\n",
			direction == DMA_MEM_TO_DEV ? "TO DEVICE" : "FROM DEVICE",
			&buf_addr,
			periods, buf_len, period_len);

	if (unlikely(!atslave || !buf_len || !period_len)) {
		dev_dbg(chan2dev(chan), "prep_dma_cyclic: length is zero!\n");
		return NULL;
	}

	was_cyclic = test_and_set_bit(ATC_IS_CYCLIC, &atchan->status);
	if (was_cyclic) {
		dev_dbg(chan2dev(chan), "prep_dma_cyclic: channel in use!\n");
		return NULL;
	}

	if (unlikely(!is_slave_direction(direction)))
		goto err_out;

	if (direction == DMA_MEM_TO_DEV)
		reg_width = convert_buswidth(sconfig->dst_addr_width);
	else
		reg_width = convert_buswidth(sconfig->src_addr_width);

	/* Check for too big/unaligned periods and unaligned DMA buffer */
	if (atc_dma_cyclic_check_values(reg_width, buf_addr, period_len))
		goto err_out;

	/* build cyclic linked list */
	for (i = 0; i < periods; i++) {
		struct at_desc	*desc;

		desc = atc_desc_get(atchan);
		if (!desc)
			goto err_desc_get;

		if (atc_dma_cyclic_fill_desc(chan, desc, i, buf_addr,
					     reg_width, period_len, direction))
			goto err_desc_get;

		atc_desc_chain(&first, &prev, desc);
	}

	/* lets make a cyclic list */
	prev->lli.dscr = first->txd.phys;

	/* First descriptor of the chain embedds additional information */
	first->txd.cookie = -EBUSY;
	first->total_len = buf_len;

	return &first->txd;

err_desc_get:
	dev_err(chan2dev(chan), "not enough descriptors available\n");
	atc_desc_put(atchan, first);
err_out:
	clear_bit(ATC_IS_CYCLIC, &atchan->status);
	return NULL;
}