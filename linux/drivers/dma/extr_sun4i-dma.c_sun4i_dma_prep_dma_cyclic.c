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
typedef  int u32 ;
struct dma_slave_config {scalar_t__ src_addr; scalar_t__ dst_addr; } ;
struct sun4i_dma_vchan {int /*<<< orphan*/  vc; int /*<<< orphan*/  endpoint; scalar_t__ is_dedicated; struct dma_slave_config cfg; } ;
struct sun4i_dma_promise {int cfg; int /*<<< orphan*/  list; } ;
struct sun4i_dma_contract {int is_cyclic; int /*<<< orphan*/  vd; int /*<<< orphan*/  demands; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DIV_ROUND_UP (size_t,int) ; 
 int DMA_MEM_TO_DEV ; 
 int SUN4I_DMA_CFG_DST_ADDR_MODE (int /*<<< orphan*/ ) ; 
 int SUN4I_DMA_CFG_DST_DRQ_TYPE (int /*<<< orphan*/ ) ; 
 int SUN4I_DMA_CFG_SRC_ADDR_MODE (int /*<<< orphan*/ ) ; 
 int SUN4I_DMA_CFG_SRC_DRQ_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_NDMA_ADDR_MODE_IO ; 
 int /*<<< orphan*/  SUN4I_NDMA_DRQ_TYPE_SDRAM ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sun4i_dma_contract* generate_dma_contract () ; 
 struct sun4i_dma_promise* generate_ndma_promise (struct dma_chan*,scalar_t__,scalar_t__,int,struct dma_slave_config*,int) ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int min (size_t,size_t) ; 
 struct sun4i_dma_vchan* to_sun4i_dma_vchan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
sun4i_dma_prep_dma_cyclic(struct dma_chan *chan, dma_addr_t buf, size_t len,
			  size_t period_len, enum dma_transfer_direction dir,
			  unsigned long flags)
{
	struct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	struct dma_slave_config *sconfig = &vchan->cfg;
	struct sun4i_dma_promise *promise;
	struct sun4i_dma_contract *contract;
	dma_addr_t src, dest;
	u32 endpoints;
	int nr_periods, offset, plength, i;

	if (!is_slave_direction(dir)) {
		dev_err(chan2dev(chan), "Invalid DMA direction\n");
		return NULL;
	}

	if (vchan->is_dedicated) {
		/*
		 * As we are using this just for audio data, we need to use
		 * normal DMA. There is nothing stopping us from supporting
		 * dedicated DMA here as well, so if a client comes up and
		 * requires it, it will be simple to implement it.
		 */
		dev_err(chan2dev(chan),
			"Cyclic transfers are only supported on Normal DMA\n");
		return NULL;
	}

	contract = generate_dma_contract();
	if (!contract)
		return NULL;

	contract->is_cyclic = 1;

	/* Figure out the endpoints and the address we need */
	if (dir == DMA_MEM_TO_DEV) {
		src = buf;
		dest = sconfig->dst_addr;
		endpoints = SUN4I_DMA_CFG_SRC_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM) |
			    SUN4I_DMA_CFG_DST_DRQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_DST_ADDR_MODE(SUN4I_NDMA_ADDR_MODE_IO);
	} else {
		src = sconfig->src_addr;
		dest = buf;
		endpoints = SUN4I_DMA_CFG_SRC_DRQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_SRC_ADDR_MODE(SUN4I_NDMA_ADDR_MODE_IO) |
			    SUN4I_DMA_CFG_DST_DRQ_TYPE(SUN4I_NDMA_DRQ_TYPE_SDRAM);
	}

	/*
	 * We will be using half done interrupts to make two periods
	 * out of a promise, so we need to program the DMA engine less
	 * often
	 */

	/*
	 * The engine can interrupt on half-transfer, so we can use
	 * this feature to program the engine half as often as if we
	 * didn't use it (keep in mind the hardware doesn't support
	 * linked lists).
	 *
	 * Say you have a set of periods (| marks the start/end, I for
	 * interrupt, P for programming the engine to do a new
	 * transfer), the easy but slow way would be to do
	 *
	 *  |---|---|---|---| (periods / promises)
	 *  P  I,P I,P I,P  I
	 *
	 * Using half transfer interrupts you can do
	 *
	 *  |-------|-------| (promises as configured on hw)
	 *  |---|---|---|---| (periods)
	 *  P   I  I,P  I   I
	 *
	 * Which requires half the engine programming for the same
	 * functionality.
	 */
	nr_periods = DIV_ROUND_UP(len / period_len, 2);
	for (i = 0; i < nr_periods; i++) {
		/* Calculate the offset in the buffer and the length needed */
		offset = i * period_len * 2;
		plength = min((len - offset), (period_len * 2));
		if (dir == DMA_MEM_TO_DEV)
			src = buf + offset;
		else
			dest = buf + offset;

		/* Make the promise */
		promise = generate_ndma_promise(chan, src, dest,
						plength, sconfig, dir);
		if (!promise) {
			/* TODO: should we free everything? */
			return NULL;
		}
		promise->cfg |= endpoints;

		/* Then add it to the contract */
		list_add_tail(&promise->list, &contract->demands);
	}

	/* And add it to the vchan */
	return vchan_tx_prep(&vchan->vc, &contract->vd, flags);
}