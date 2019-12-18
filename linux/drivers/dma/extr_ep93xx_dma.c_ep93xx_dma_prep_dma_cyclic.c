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
struct dma_async_tx_descriptor {int /*<<< orphan*/  cookie; } ;
struct ep93xx_dma_desc {size_t size; struct dma_async_tx_descriptor txd; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  node; void* dst_addr; void* src_addr; } ;
struct ep93xx_dma_chan {void* runtime_addr; int /*<<< orphan*/  slave_config; int /*<<< orphan*/  flags; TYPE_1__* edma; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  m2m; } ;

/* Variables and functions */
 size_t DMA_MAX_CHAN_BYTES ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EP93XX_DMA_IS_CYCLIC ; 
 int /*<<< orphan*/  chan2dev (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int ep93xx_dma_chan_direction (struct dma_chan*) ; 
 struct ep93xx_dma_desc* ep93xx_dma_desc_get (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  ep93xx_dma_desc_put (struct ep93xx_dma_chan*,struct ep93xx_dma_desc*) ; 
 int /*<<< orphan*/  ep93xx_dma_slave_config_write (struct dma_chan*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ep93xx_dma_chan* to_ep93xx_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
ep93xx_dma_prep_dma_cyclic(struct dma_chan *chan, dma_addr_t dma_addr,
			   size_t buf_len, size_t period_len,
			   enum dma_transfer_direction dir, unsigned long flags)
{
	struct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	struct ep93xx_dma_desc *desc, *first;
	size_t offset = 0;

	if (!edmac->edma->m2m && dir != ep93xx_dma_chan_direction(chan)) {
		dev_warn(chan2dev(edmac),
			 "channel was configured with different direction\n");
		return NULL;
	}

	if (test_and_set_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags)) {
		dev_warn(chan2dev(edmac),
			 "channel is already used for cyclic transfers\n");
		return NULL;
	}

	if (period_len > DMA_MAX_CHAN_BYTES) {
		dev_warn(chan2dev(edmac), "too big period length %zu\n",
			 period_len);
		return NULL;
	}

	ep93xx_dma_slave_config_write(chan, dir, &edmac->slave_config);

	/* Split the buffer into period size chunks */
	first = NULL;
	for (offset = 0; offset < buf_len; offset += period_len) {
		desc = ep93xx_dma_desc_get(edmac);
		if (!desc) {
			dev_warn(chan2dev(edmac), "couldn't get descriptor\n");
			goto fail;
		}

		if (dir == DMA_MEM_TO_DEV) {
			desc->src_addr = dma_addr + offset;
			desc->dst_addr = edmac->runtime_addr;
		} else {
			desc->src_addr = edmac->runtime_addr;
			desc->dst_addr = dma_addr + offset;
		}

		desc->size = period_len;

		if (!first)
			first = desc;
		else
			list_add_tail(&desc->node, &first->tx_list);
	}

	first->txd.cookie = -EBUSY;

	return &first->txd;

fail:
	ep93xx_dma_desc_put(edmac, first);
	return NULL;
}