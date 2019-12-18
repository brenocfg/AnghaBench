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
struct ath_txq {int dummy; } ;
struct ath_tid {int /*<<< orphan*/  hwq_depth; } ;
struct ath_softc {int dummy; } ;
struct ath_node {struct ath_tid* an_tid; } ;
struct TYPE_2__ {size_t bfs_tid; int /*<<< orphan*/  bfs_txflags; } ;
struct ath_buf {int /*<<< orphan*/  bf_comp; TYPE_1__ bf_state; int /*<<< orphan*/  bf_node; } ;

/* Variables and functions */
 struct ath_node* ATH_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_TXDESC_CLRDMASK ; 
 int /*<<< orphan*/  ath_tx_calc_duration (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_calc_protection (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_do_ratelookup (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_handoff (struct ath_softc*,struct ath_txq*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_normal_comp ; 
 int /*<<< orphan*/  ath_tx_rate_fill_rcflags (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_set_rtscts (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_tx_setds (struct ath_softc*,struct ath_buf*) ; 

__attribute__((used)) static void
ath_tx_xmit_normal(struct ath_softc *sc, struct ath_txq *txq,
    struct ath_buf *bf)
{
	struct ath_node *an = ATH_NODE(bf->bf_node);
	struct ath_tid *tid = &an->an_tid[bf->bf_state.bfs_tid];

	ATH_TX_LOCK_ASSERT(sc);

	/*
	 * For now, just enable CLRDMASK. ath_tx_xmit_normal() does
	 * set a completion handler however it doesn't (yet) properly
	 * handle the strict ordering requirements needed for normal,
	 * non-aggregate session frames.
	 *
	 * Once this is implemented, only set CLRDMASK like this for
	 * frames that must go out - eg management/raw frames.
	 */
	bf->bf_state.bfs_txflags |= HAL_TXDESC_CLRDMASK;

	/* Setup the descriptor before handoff */
	ath_tx_do_ratelookup(sc, bf);
	ath_tx_calc_duration(sc, bf);
	ath_tx_calc_protection(sc, bf);
	ath_tx_set_rtscts(sc, bf);
	ath_tx_rate_fill_rcflags(sc, bf);
	ath_tx_setds(sc, bf);

	/* Track per-TID hardware queue depth correctly */
	tid->hwq_depth++;

	/* Assign the completion handler */
	bf->bf_comp = ath_tx_normal_comp;

	/* Hand off to hardware */
	ath_tx_handoff(sc, txq, bf);
}