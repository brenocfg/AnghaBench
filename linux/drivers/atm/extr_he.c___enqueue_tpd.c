#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct he_tpdrq {unsigned int cid; int /*<<< orphan*/  tpd; } ;
struct he_tpd {int /*<<< orphan*/  status; int /*<<< orphan*/  entry; TYPE_4__* vcc; scalar_t__ skb; TYPE_2__* iovec; } ;
struct he_dev {struct he_tpdrq* tpdrq_tail; int /*<<< orphan*/  outstanding_tpds; int /*<<< orphan*/  tpd_pool; TYPE_1__* pci_dev; struct he_tpdrq* tpdrq_head; scalar_t__ tpdrq_base; } ;
struct TYPE_8__ {TYPE_3__* stats; int /*<<< orphan*/  (* pop ) (TYPE_4__*,scalar_t__) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  tx_err; } ;
struct TYPE_6__ {int len; scalar_t__ addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  HPRINTK (char*,struct he_tpd*,unsigned int,struct he_tpdrq*) ; 
 int /*<<< orphan*/  TPDRQ_B_H ; 
 unsigned long TPDRQ_MASK (struct he_tpdrq*) ; 
 int /*<<< orphan*/  TPDRQ_T ; 
 int /*<<< orphan*/  TPD_ADDR (int /*<<< orphan*/ ) ; 
 int TPD_LEN_MASK ; 
 int TPD_MAXIOV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct he_tpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct he_tpdrq* he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static __inline__ void
__enqueue_tpd(struct he_dev *he_dev, struct he_tpd *tpd, unsigned cid)
{
	struct he_tpdrq *new_tail;

	HPRINTK("tpdrq %p cid 0x%x -> tpdrq_tail %p\n",
					tpd, cid, he_dev->tpdrq_tail);

	/* new_tail = he_dev->tpdrq_tail; */
	new_tail = (struct he_tpdrq *) ((unsigned long) he_dev->tpdrq_base |
					TPDRQ_MASK(he_dev->tpdrq_tail+1));

	/*
	 * check to see if we are about to set the tail == head
	 * if true, update the head pointer from the adapter
	 * to see if this is really the case (reading the queue
	 * head for every enqueue would be unnecessarily slow)
	 */

	if (new_tail == he_dev->tpdrq_head) {
		he_dev->tpdrq_head = (struct he_tpdrq *)
			(((unsigned long)he_dev->tpdrq_base) |
				TPDRQ_MASK(he_readl(he_dev, TPDRQ_B_H)));

		if (new_tail == he_dev->tpdrq_head) {
			int slot;

			hprintk("tpdrq full (cid 0x%x)\n", cid);
			/*
			 * FIXME
			 * push tpd onto a transmit backlog queue
			 * after service_tbrq, service the backlog
			 * for now, we just drop the pdu
			 */
			for (slot = 0; slot < TPD_MAXIOV; ++slot) {
				if (tpd->iovec[slot].addr)
					dma_unmap_single(&he_dev->pci_dev->dev,
						tpd->iovec[slot].addr,
						tpd->iovec[slot].len & TPD_LEN_MASK,
								DMA_TO_DEVICE);
			}
			if (tpd->skb) {
				if (tpd->vcc->pop)
					tpd->vcc->pop(tpd->vcc, tpd->skb);
				else
					dev_kfree_skb_any(tpd->skb);
				atomic_inc(&tpd->vcc->stats->tx_err);
			}
			dma_pool_free(he_dev->tpd_pool, tpd, TPD_ADDR(tpd->status));
			return;
		}
	}

	/* 2.1.5 transmit packet descriptor ready queue */
	list_add_tail(&tpd->entry, &he_dev->outstanding_tpds);
	he_dev->tpdrq_tail->tpd = TPD_ADDR(tpd->status);
	he_dev->tpdrq_tail->cid = cid;
	wmb();

	he_dev->tpdrq_tail = new_tail;

	he_writel(he_dev, TPDRQ_MASK(he_dev->tpdrq_tail), TPDRQ_T);
	(void) he_readl(he_dev, TPDRQ_T);		/* flush posted writes */
}