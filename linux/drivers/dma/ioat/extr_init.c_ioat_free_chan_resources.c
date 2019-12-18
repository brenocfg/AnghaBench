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
struct ioatdma_device {scalar_t__ version; int /*<<< orphan*/  completion_pool; } ;
struct ioatdma_chan {int alloc_order; int desc_chunks; scalar_t__ dmacount; scalar_t__ completion_dma; scalar_t__ last_completion; int /*<<< orphan*/  cleanup_lock; int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  completion; int /*<<< orphan*/ * ring; TYPE_1__* descs; scalar_t__ tail; scalar_t__ head; scalar_t__ reg_base; struct ioatdma_device* ioat_dma; } ;
struct ioat_ring_ent {int dummy; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {scalar_t__ hw; int /*<<< orphan*/ * virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHAN_LTR_SWSEL_IDLE ; 
 scalar_t__ IOAT_CHAN_LTR_SWSEL_OFFSET ; 
 scalar_t__ IOAT_VER_3_4 ; 
 int /*<<< orphan*/  SZ_2M ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dump_desc_dbg (struct ioatdma_chan*,struct ioat_ring_ent*) ; 
 int /*<<< orphan*/  ioat_free_ring_ent (struct ioat_ring_ent*,struct dma_chan*) ; 
 struct ioat_ring_ent* ioat_get_ring_ent (struct ioatdma_chan*,scalar_t__) ; 
 int /*<<< orphan*/  ioat_reset_hw (struct ioatdma_chan*) ; 
 int ioat_ring_space (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  ioat_stop (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_dev (struct ioatdma_chan*) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ioat_free_chan_resources(struct dma_chan *c)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	struct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	struct ioat_ring_ent *desc;
	const int total_descs = 1 << ioat_chan->alloc_order;
	int descs;
	int i;

	/* Before freeing channel resources first check
	 * if they have been previously allocated for this channel.
	 */
	if (!ioat_chan->ring)
		return;

	ioat_stop(ioat_chan);
	ioat_reset_hw(ioat_chan);

	/* Put LTR to idle */
	if (ioat_dma->version >= IOAT_VER_3_4)
		writeb(IOAT_CHAN_LTR_SWSEL_IDLE,
			ioat_chan->reg_base + IOAT_CHAN_LTR_SWSEL_OFFSET);

	spin_lock_bh(&ioat_chan->cleanup_lock);
	spin_lock_bh(&ioat_chan->prep_lock);
	descs = ioat_ring_space(ioat_chan);
	dev_dbg(to_dev(ioat_chan), "freeing %d idle descriptors\n", descs);
	for (i = 0; i < descs; i++) {
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->head + i);
		ioat_free_ring_ent(desc, c);
	}

	if (descs < total_descs)
		dev_err(to_dev(ioat_chan), "Freeing %d in use descriptors!\n",
			total_descs - descs);

	for (i = 0; i < total_descs - descs; i++) {
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->tail + i);
		dump_desc_dbg(ioat_chan, desc);
		ioat_free_ring_ent(desc, c);
	}

	for (i = 0; i < ioat_chan->desc_chunks; i++) {
		dma_free_coherent(to_dev(ioat_chan), SZ_2M,
				  ioat_chan->descs[i].virt,
				  ioat_chan->descs[i].hw);
		ioat_chan->descs[i].virt = NULL;
		ioat_chan->descs[i].hw = 0;
	}
	ioat_chan->desc_chunks = 0;

	kfree(ioat_chan->ring);
	ioat_chan->ring = NULL;
	ioat_chan->alloc_order = 0;
	dma_pool_free(ioat_dma->completion_pool, ioat_chan->completion,
		      ioat_chan->completion_dma);
	spin_unlock_bh(&ioat_chan->prep_lock);
	spin_unlock_bh(&ioat_chan->cleanup_lock);

	ioat_chan->last_completion = 0;
	ioat_chan->completion_dma = 0;
	ioat_chan->dmacount = 0;
}