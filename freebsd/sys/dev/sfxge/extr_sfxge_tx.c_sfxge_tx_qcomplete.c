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
struct sfxge_txq {unsigned int completed; unsigned int pending; unsigned int ptr_mask; unsigned int added; int /*<<< orphan*/  entries; scalar_t__ blocked; int /*<<< orphan*/  packet_dma_tag; struct sfxge_tx_mapping* stmp; } ;
struct TYPE_2__ {int /*<<< orphan*/  heap_buf; struct mbuf* mbuf; } ;
struct sfxge_tx_mapping {int flags; TYPE_1__ u; int /*<<< orphan*/  map; } ;
struct sfxge_evq {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SFXGE ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 unsigned int SFXGE_TXQ_UNBLOCK_LEVEL (int /*<<< orphan*/ ) ; 
 int TX_BUF_MBUF ; 
 int TX_BUF_UNMAP ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* m_free (struct mbuf*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  sfxge_tx_qunblock (struct sfxge_txq*) ; 

void
sfxge_tx_qcomplete(struct sfxge_txq *txq, struct sfxge_evq *evq)
{
	unsigned int completed;

	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	completed = txq->completed;
	while (completed != txq->pending) {
		struct sfxge_tx_mapping *stmp;
		unsigned int id;

		id = completed++ & txq->ptr_mask;

		stmp = &txq->stmp[id];
		if (stmp->flags & TX_BUF_UNMAP) {
			bus_dmamap_unload(txq->packet_dma_tag, stmp->map);
			if (stmp->flags & TX_BUF_MBUF) {
				struct mbuf *m = stmp->u.mbuf;
				do
					m = m_free(m);
				while (m != NULL);
			} else {
				free(stmp->u.heap_buf, M_SFXGE);
			}
			stmp->flags = 0;
		}
	}
	txq->completed = completed;

	/* Check whether we need to unblock the queue. */
	mb();
	if (txq->blocked) {
		unsigned int level;

		level = txq->added - txq->completed;
		if (level <= SFXGE_TXQ_UNBLOCK_LEVEL(txq->entries))
			sfxge_tx_qunblock(txq);
	}
}