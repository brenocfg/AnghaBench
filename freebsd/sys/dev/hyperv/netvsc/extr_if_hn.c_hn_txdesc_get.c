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
struct hn_txdesc {int refs; scalar_t__ chim_index; scalar_t__ chim_size; int flags; int /*<<< orphan*/  agg_list; int /*<<< orphan*/ * m; } ;
struct hn_tx_ring {scalar_t__ hn_txdesc_avail; int /*<<< orphan*/  hn_txdesc_br; int /*<<< orphan*/  hn_txlist_spin; int /*<<< orphan*/  hn_txlist; } ;

/* Variables and functions */
 scalar_t__ HN_NVS_CHIM_IDX_INVALID ; 
 int HN_TXD_FLAG_DMAMAP ; 
 int HN_TXD_FLAG_ONAGG ; 
 int HN_TXD_FLAG_ONLIST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct hn_txdesc* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 struct hn_txdesc* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline struct hn_txdesc *
hn_txdesc_get(struct hn_tx_ring *txr)
{
	struct hn_txdesc *txd;

#ifndef HN_USE_TXDESC_BUFRING
	mtx_lock_spin(&txr->hn_txlist_spin);
	txd = SLIST_FIRST(&txr->hn_txlist);
	if (txd != NULL) {
		KASSERT(txr->hn_txdesc_avail > 0,
		    ("txdesc_get: invalid txd avail %d", txr->hn_txdesc_avail));
		txr->hn_txdesc_avail--;
		SLIST_REMOVE_HEAD(&txr->hn_txlist, link);
	}
	mtx_unlock_spin(&txr->hn_txlist_spin);
#else
	txd = buf_ring_dequeue_sc(txr->hn_txdesc_br);
#endif

	if (txd != NULL) {
#ifdef HN_USE_TXDESC_BUFRING
#ifdef HN_DEBUG
		atomic_subtract_int(&txr->hn_txdesc_avail, 1);
#endif
#endif	/* HN_USE_TXDESC_BUFRING */
		KASSERT(txd->m == NULL && txd->refs == 0 &&
		    STAILQ_EMPTY(&txd->agg_list) &&
		    txd->chim_index == HN_NVS_CHIM_IDX_INVALID &&
		    txd->chim_size == 0 &&
		    (txd->flags & HN_TXD_FLAG_ONLIST) &&
		    (txd->flags & HN_TXD_FLAG_ONAGG) == 0 &&
		    (txd->flags & HN_TXD_FLAG_DMAMAP) == 0, ("invalid txd"));
		txd->flags &= ~HN_TXD_FLAG_ONLIST;
		txd->refs = 1;
	}
	return txd;
}