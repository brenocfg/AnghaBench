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
struct dma_slave_config {scalar_t__ src_addr; scalar_t__ dst_addr; } ;
struct owl_dma_vchan {int /*<<< orphan*/  vc; struct dma_slave_config cfg; } ;
struct owl_dma_txd {int cyclic; int /*<<< orphan*/  vd; int /*<<< orphan*/  lli_list; } ;
struct owl_dma_lli {int dummy; } ;
struct owl_dma {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct owl_dma_txd* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct owl_dma_lli* owl_dma_add_lli (struct owl_dma_txd*,struct owl_dma_lli*,struct owl_dma_lli*,int) ; 
 struct owl_dma_lli* owl_dma_alloc_lli (struct owl_dma*) ; 
 int owl_dma_cfg_lli (struct owl_dma_vchan*,struct owl_dma_lli*,scalar_t__,scalar_t__,size_t,int,struct dma_slave_config*,int) ; 
 int /*<<< orphan*/  owl_dma_free_txd (struct owl_dma*,struct owl_dma_txd*) ; 
 struct owl_dma* to_owl_dma (int /*<<< orphan*/ ) ; 
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor
		*owl_prep_dma_cyclic(struct dma_chan *chan,
				     dma_addr_t buf_addr, size_t buf_len,
				     size_t period_len,
				     enum dma_transfer_direction dir,
				     unsigned long flags)
{
	struct owl_dma *od = to_owl_dma(chan->device);
	struct owl_dma_vchan *vchan = to_owl_vchan(chan);
	struct dma_slave_config *sconfig = &vchan->cfg;
	struct owl_dma_txd *txd;
	struct owl_dma_lli *lli, *prev = NULL, *first = NULL;
	dma_addr_t src = 0, dst = 0;
	unsigned int periods = buf_len / period_len;
	int ret, i;

	txd = kzalloc(sizeof(*txd), GFP_NOWAIT);
	if (!txd)
		return NULL;

	INIT_LIST_HEAD(&txd->lli_list);
	txd->cyclic = true;

	for (i = 0; i < periods; i++) {
		lli = owl_dma_alloc_lli(od);
		if (!lli) {
			dev_warn(chan2dev(chan), "failed to allocate lli");
			goto err_txd_free;
		}

		if (dir == DMA_MEM_TO_DEV) {
			src = buf_addr + (period_len * i);
			dst = sconfig->dst_addr;
		} else if (dir == DMA_DEV_TO_MEM) {
			src = sconfig->src_addr;
			dst = buf_addr + (period_len * i);
		}

		ret = owl_dma_cfg_lli(vchan, lli, src, dst, period_len,
				      dir, sconfig, txd->cyclic);
		if (ret) {
			dev_warn(chan2dev(chan), "failed to config lli");
			goto err_txd_free;
		}

		if (!first)
			first = lli;

		prev = owl_dma_add_lli(txd, prev, lli, false);
	}

	/* close the cyclic list */
	owl_dma_add_lli(txd, prev, first, true);

	return vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_txd_free:
	owl_dma_free_txd(od, txd);

	return NULL;
}