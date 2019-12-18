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
struct tx_sw_desc {int flags; int /*<<< orphan*/ * m; int /*<<< orphan*/  map; } ;
struct sge_txq {int cntxt_id; unsigned int cidx; int size; struct tx_sw_desc* sdesc; int /*<<< orphan*/  txq_skipped; int /*<<< orphan*/  entry_tag; } ;
struct sge_qset {int /*<<< orphan*/  lock; struct sge_txq* txq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  T3_TRACE2 (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int TX_SW_DESC_MAPPED ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 TYPE_1__* sc ; 

void
t3_free_tx_desc(struct sge_qset *qs, int reclaimable, int queue)
{
	struct tx_sw_desc *txsd;
	unsigned int cidx, mask;
	struct sge_txq *q = &qs->txq[queue];

#ifdef T3_TRACE
	T3_TRACE2(sc->tb[q->cntxt_id & 7],
		  "reclaiming %u Tx descriptors at cidx %u", reclaimable, cidx);
#endif
	cidx = q->cidx;
	mask = q->size - 1;
	txsd = &q->sdesc[cidx];

	mtx_assert(&qs->lock, MA_OWNED);
	while (reclaimable--) {
		prefetch(q->sdesc[(cidx + 1) & mask].m);
		prefetch(q->sdesc[(cidx + 2) & mask].m);

		if (txsd->m != NULL) {
			if (txsd->flags & TX_SW_DESC_MAPPED) {
				bus_dmamap_unload(q->entry_tag, txsd->map);
				txsd->flags &= ~TX_SW_DESC_MAPPED;
			}
			m_freem_list(txsd->m);
			txsd->m = NULL;
		} else
			q->txq_skipped++;
		
		++txsd;
		if (++cidx == q->size) {
			cidx = 0;
			txsd = q->sdesc;
		}
	}
	q->cidx = cidx;

}