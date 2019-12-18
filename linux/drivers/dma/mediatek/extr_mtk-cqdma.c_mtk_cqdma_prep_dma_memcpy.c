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
struct dma_async_tx_descriptor {struct dma_async_tx_descriptor* next; } ;
struct TYPE_2__ {struct dma_async_tx_descriptor tx; } ;
struct mtk_cqdma_vdesc {size_t len; size_t src; size_t dest; size_t residue; TYPE_1__ vd; struct mtk_cqdma_vdesc* parent; struct dma_chan* ch; } ;
struct dma_chan {int dummy; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t DIV_ROUND_UP (size_t,size_t) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 size_t MTK_CQDMA_MAX_LEN ; 
 struct mtk_cqdma_vdesc** kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_cqdma_vdesc*) ; 
 struct mtk_cqdma_vdesc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_virt_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ ,TYPE_1__*,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
mtk_cqdma_prep_dma_memcpy(struct dma_chan *c, dma_addr_t dest,
			  dma_addr_t src, size_t len, unsigned long flags)
{
	struct mtk_cqdma_vdesc **cvd;
	struct dma_async_tx_descriptor *tx = NULL, *prev_tx = NULL;
	size_t i, tlen, nr_vd;

	/*
	 * In the case that trsanction length is larger than the
	 * DMA engine supports, a single memcpy transaction needs
	 * to be separated into several DMA transactions.
	 * Each DMA transaction would be described by a CVD,
	 * and the first one is referred as the parent CVD,
	 * while the others are child CVDs.
	 * The parent CVD's tx descriptor is the only tx descriptor
	 * returned to the DMA user, and it should not be completed
	 * until all the child CVDs completed.
	 */
	nr_vd = DIV_ROUND_UP(len, MTK_CQDMA_MAX_LEN);
	cvd = kcalloc(nr_vd, sizeof(*cvd), GFP_NOWAIT);
	if (!cvd)
		return NULL;

	for (i = 0; i < nr_vd; ++i) {
		cvd[i] = kzalloc(sizeof(*cvd[i]), GFP_NOWAIT);
		if (!cvd[i]) {
			for (; i > 0; --i)
				kfree(cvd[i - 1]);
			return NULL;
		}

		/* setup dma channel */
		cvd[i]->ch = c;

		/* setup sourece, destination, and length */
		tlen = (len > MTK_CQDMA_MAX_LEN) ? MTK_CQDMA_MAX_LEN : len;
		cvd[i]->len = tlen;
		cvd[i]->src = src;
		cvd[i]->dest = dest;

		/* setup tx descriptor */
		tx = vchan_tx_prep(to_virt_chan(c), &cvd[i]->vd, flags);
		tx->next = NULL;

		if (!i) {
			cvd[0]->residue = len;
		} else {
			prev_tx->next = tx;
			cvd[i]->residue = tlen;
		}

		cvd[i]->parent = cvd[0];

		/* update the src, dest, len, prev_tx for the next CVD */
		src += tlen;
		dest += tlen;
		len -= tlen;
		prev_tx = tx;
	}

	return &cvd[0]->vd.tx;
}