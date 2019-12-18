#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vtxs_omcasts; int /*<<< orphan*/  vtxs_obytes; int /*<<< orphan*/  vtxs_opackets; } ;
struct vtnet_txq {scalar_t__ vtntx_watchdog; TYPE_2__ vtntx_stats; struct virtqueue* vtntx_vq; } ;
struct vtnet_tx_header {struct mbuf* vth_mbuf; } ;
struct virtqueue {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_MCAST ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK_ASSERT (struct vtnet_txq*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct vtnet_tx_header*) ; 
 struct vtnet_tx_header* virtqueue_dequeue (struct virtqueue*,int /*<<< orphan*/ *) ; 
 scalar_t__ virtqueue_empty (struct virtqueue*) ; 
 int /*<<< orphan*/  vtnet_tx_header_zone ; 

__attribute__((used)) static int
vtnet_txq_eof(struct vtnet_txq *txq)
{
	struct virtqueue *vq;
	struct vtnet_tx_header *txhdr;
	struct mbuf *m;
	int deq;

	vq = txq->vtntx_vq;
	deq = 0;
	VTNET_TXQ_LOCK_ASSERT(txq);

	while ((txhdr = virtqueue_dequeue(vq, NULL)) != NULL) {
		m = txhdr->vth_mbuf;
		deq++;

		txq->vtntx_stats.vtxs_opackets++;
		txq->vtntx_stats.vtxs_obytes += m->m_pkthdr.len;
		if (m->m_flags & M_MCAST)
			txq->vtntx_stats.vtxs_omcasts++;

		m_freem(m);
		uma_zfree(vtnet_tx_header_zone, txhdr);
	}

	if (virtqueue_empty(vq))
		txq->vtntx_watchdog = 0;

	return (deq);
}