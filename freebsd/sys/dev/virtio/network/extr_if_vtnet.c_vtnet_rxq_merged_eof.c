#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rx_mergeable_failed; } ;
struct vtnet_softc {TYPE_3__ vtnet_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  vrxs_iqdrops; int /*<<< orphan*/  vrxs_ierrors; } ;
struct vtnet_rxq {TYPE_1__ vtnrx_stats; struct virtqueue* vtnrx_vq; struct vtnet_softc* vtnrx_sc; } ;
struct virtqueue {int dummy; } ;
struct TYPE_5__ {int len; } ;
struct mbuf {int m_len; struct mbuf* m_next; TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* virtqueue_dequeue (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  vtnet_rxq_discard_buf (struct vtnet_rxq*,struct mbuf*) ; 
 int /*<<< orphan*/  vtnet_rxq_discard_merged_bufs (struct vtnet_rxq*,int) ; 
 scalar_t__ vtnet_rxq_new_buf (struct vtnet_rxq*) ; 

__attribute__((used)) static int
vtnet_rxq_merged_eof(struct vtnet_rxq *rxq, struct mbuf *m_head, int nbufs)
{
	struct vtnet_softc *sc;
	struct virtqueue *vq;
	struct mbuf *m, *m_tail;
	int len;

	sc = rxq->vtnrx_sc;
	vq = rxq->vtnrx_vq;
	m_tail = m_head;

	while (--nbufs > 0) {
		m = virtqueue_dequeue(vq, &len);
		if (m == NULL) {
			rxq->vtnrx_stats.vrxs_ierrors++;
			goto fail;
		}

		if (vtnet_rxq_new_buf(rxq) != 0) {
			rxq->vtnrx_stats.vrxs_iqdrops++;
			vtnet_rxq_discard_buf(rxq, m);
			if (nbufs > 1)
				vtnet_rxq_discard_merged_bufs(rxq, nbufs);
			goto fail;
		}

		if (m->m_len < len)
			len = m->m_len;

		m->m_len = len;
		m->m_flags &= ~M_PKTHDR;

		m_head->m_pkthdr.len += len;
		m_tail->m_next = m;
		m_tail = m;
	}

	return (0);

fail:
	sc->vtnet_stats.rx_mergeable_failed++;
	m_freem(m_head);

	return (1);
}