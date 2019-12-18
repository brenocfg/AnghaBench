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
struct hn_txdesc {int flags; scalar_t__ refs; scalar_t__ chim_index; scalar_t__ chim_size; int /*<<< orphan*/ * m; int /*<<< orphan*/  data_dmap; int /*<<< orphan*/  agg_list; } ;
struct hn_tx_ring {scalar_t__ hn_txdesc_avail; scalar_t__ hn_txdesc_cnt; int /*<<< orphan*/  hn_txdesc_br; int /*<<< orphan*/  hn_txlist_spin; int /*<<< orphan*/  hn_txlist; int /*<<< orphan*/  hn_tx_data_dtag; int /*<<< orphan*/  hn_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ HN_NVS_CHIM_IDX_INVALID ; 
 int HN_TXD_FLAG_DMAMAP ; 
 int HN_TXD_FLAG_ONAGG ; 
 int HN_TXD_FLAG_ONLIST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hn_txdesc*,int /*<<< orphan*/ ) ; 
 int STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct hn_txdesc* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_link ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 
 int atomic_fetchadd_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  buf_ring_enqueue (int /*<<< orphan*/ ,struct hn_txdesc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_chim_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
hn_txdesc_put(struct hn_tx_ring *txr, struct hn_txdesc *txd)
{

	KASSERT((txd->flags & HN_TXD_FLAG_ONLIST) == 0,
	    ("put an onlist txd %#x", txd->flags));
	KASSERT((txd->flags & HN_TXD_FLAG_ONAGG) == 0,
	    ("put an onagg txd %#x", txd->flags));

	KASSERT(txd->refs > 0, ("invalid txd refs %d", txd->refs));
	if (atomic_fetchadd_int(&txd->refs, -1) != 1)
		return 0;

	if (!STAILQ_EMPTY(&txd->agg_list)) {
		struct hn_txdesc *tmp_txd;

		while ((tmp_txd = STAILQ_FIRST(&txd->agg_list)) != NULL) {
			int freed;

			KASSERT(STAILQ_EMPTY(&tmp_txd->agg_list),
			    ("resursive aggregation on aggregated txdesc"));
			KASSERT((tmp_txd->flags & HN_TXD_FLAG_ONAGG),
			    ("not aggregated txdesc"));
			KASSERT((tmp_txd->flags & HN_TXD_FLAG_DMAMAP) == 0,
			    ("aggregated txdesc uses dmamap"));
			KASSERT(tmp_txd->chim_index == HN_NVS_CHIM_IDX_INVALID,
			    ("aggregated txdesc consumes "
			     "chimney sending buffer"));
			KASSERT(tmp_txd->chim_size == 0,
			    ("aggregated txdesc has non-zero "
			     "chimney sending size"));

			STAILQ_REMOVE_HEAD(&txd->agg_list, agg_link);
			tmp_txd->flags &= ~HN_TXD_FLAG_ONAGG;
			freed = hn_txdesc_put(txr, tmp_txd);
			KASSERT(freed, ("failed to free aggregated txdesc"));
		}
	}

	if (txd->chim_index != HN_NVS_CHIM_IDX_INVALID) {
		KASSERT((txd->flags & HN_TXD_FLAG_DMAMAP) == 0,
		    ("chim txd uses dmamap"));
		hn_chim_free(txr->hn_sc, txd->chim_index);
		txd->chim_index = HN_NVS_CHIM_IDX_INVALID;
		txd->chim_size = 0;
	} else if (txd->flags & HN_TXD_FLAG_DMAMAP) {
		bus_dmamap_sync(txr->hn_tx_data_dtag,
		    txd->data_dmap, BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(txr->hn_tx_data_dtag,
		    txd->data_dmap);
		txd->flags &= ~HN_TXD_FLAG_DMAMAP;
	}

	if (txd->m != NULL) {
		m_freem(txd->m);
		txd->m = NULL;
	}

	txd->flags |= HN_TXD_FLAG_ONLIST;
#ifndef HN_USE_TXDESC_BUFRING
	mtx_lock_spin(&txr->hn_txlist_spin);
	KASSERT(txr->hn_txdesc_avail >= 0 &&
	    txr->hn_txdesc_avail < txr->hn_txdesc_cnt,
	    ("txdesc_put: invalid txd avail %d", txr->hn_txdesc_avail));
	txr->hn_txdesc_avail++;
	SLIST_INSERT_HEAD(&txr->hn_txlist, txd, link);
	mtx_unlock_spin(&txr->hn_txlist_spin);
#else	/* HN_USE_TXDESC_BUFRING */
#ifdef HN_DEBUG
	atomic_add_int(&txr->hn_txdesc_avail, 1);
#endif
	buf_ring_enqueue(txr->hn_txdesc_br, txd);
#endif	/* !HN_USE_TXDESC_BUFRING */

	return 1;
}