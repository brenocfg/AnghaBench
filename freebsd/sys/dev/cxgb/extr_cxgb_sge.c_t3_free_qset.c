#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  desc_map; scalar_t__ desc; int /*<<< orphan*/  cntxt_id; } ;
struct sge_qset {TYPE_4__ lro; TYPE_3__ rspq; TYPE_1__* txq; int /*<<< orphan*/  lock; TYPE_11__* fl; } ;
struct TYPE_14__ {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_17__ {TYPE_2__ sge; } ;
typedef  TYPE_5__ adapter_t ;
struct TYPE_13__ {int /*<<< orphan*/ * sdesc; int /*<<< orphan*/  entry_tag; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  desc_map; scalar_t__ desc; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/ * txq_ifq; int /*<<< orphan*/ * txq_mr; } ;
struct TYPE_12__ {int /*<<< orphan*/ * sdesc; int /*<<< orphan*/  entry_tag; int /*<<< orphan*/  desc_tag; int /*<<< orphan*/  desc_map; scalar_t__ desc; int /*<<< orphan*/  cntxt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int SGE_RXQ_PER_SET ; 
 int SGE_TXQ_PER_SET ; 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sge_qset*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rx_bufs (TYPE_5__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ifq_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge_qset*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  t3_sge_disable_fl (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_sge_disable_rspcntxt (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_sge_enable_ecntxt (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
t3_free_qset(adapter_t *sc, struct sge_qset *q)
{
	int i;
	
	reclaim_completed_tx(q, 0, TXQ_ETH);
	if (q->txq[TXQ_ETH].txq_mr != NULL) 
		buf_ring_free(q->txq[TXQ_ETH].txq_mr, M_DEVBUF);
	if (q->txq[TXQ_ETH].txq_ifq != NULL) {
		ifq_delete(q->txq[TXQ_ETH].txq_ifq);
		free(q->txq[TXQ_ETH].txq_ifq, M_DEVBUF);
	}

	for (i = 0; i < SGE_RXQ_PER_SET; ++i) {
		if (q->fl[i].desc) {
			mtx_lock_spin(&sc->sge.reg_lock);
			t3_sge_disable_fl(sc, q->fl[i].cntxt_id);
			mtx_unlock_spin(&sc->sge.reg_lock);
			bus_dmamap_unload(q->fl[i].desc_tag, q->fl[i].desc_map);
			bus_dmamem_free(q->fl[i].desc_tag, q->fl[i].desc,
					q->fl[i].desc_map);
			bus_dma_tag_destroy(q->fl[i].desc_tag);
			bus_dma_tag_destroy(q->fl[i].entry_tag);
		}
		if (q->fl[i].sdesc) {
			free_rx_bufs(sc, &q->fl[i]);
			free(q->fl[i].sdesc, M_DEVBUF);
		}
	}

	mtx_unlock(&q->lock);
	MTX_DESTROY(&q->lock);
	for (i = 0; i < SGE_TXQ_PER_SET; i++) {
		if (q->txq[i].desc) {
			mtx_lock_spin(&sc->sge.reg_lock);
			t3_sge_enable_ecntxt(sc, q->txq[i].cntxt_id, 0);
			mtx_unlock_spin(&sc->sge.reg_lock);
			bus_dmamap_unload(q->txq[i].desc_tag,
					q->txq[i].desc_map);
			bus_dmamem_free(q->txq[i].desc_tag, q->txq[i].desc,
					q->txq[i].desc_map);
			bus_dma_tag_destroy(q->txq[i].desc_tag);
			bus_dma_tag_destroy(q->txq[i].entry_tag);
		}
		if (q->txq[i].sdesc) {
			free(q->txq[i].sdesc, M_DEVBUF);
		}
	}

	if (q->rspq.desc) {
		mtx_lock_spin(&sc->sge.reg_lock);
		t3_sge_disable_rspcntxt(sc, q->rspq.cntxt_id);
		mtx_unlock_spin(&sc->sge.reg_lock);
		
		bus_dmamap_unload(q->rspq.desc_tag, q->rspq.desc_map);
		bus_dmamem_free(q->rspq.desc_tag, q->rspq.desc,
			        q->rspq.desc_map);
		bus_dma_tag_destroy(q->rspq.desc_tag);
		MTX_DESTROY(&q->rspq.lock);
	}

#if defined(INET6) || defined(INET)
	tcp_lro_free(&q->lro.ctrl);
#endif

	bzero(q, sizeof(*q));
}