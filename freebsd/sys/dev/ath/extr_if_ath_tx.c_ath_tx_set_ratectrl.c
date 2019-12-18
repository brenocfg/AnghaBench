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
struct ieee80211_node {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_rc_series {int tries; int /*<<< orphan*/  ratecode; } ;
struct TYPE_2__ {int bfs_txflags; int /*<<< orphan*/  bfs_ismrr; struct ath_rc_series* bfs_rc; } ;
struct ath_buf {int /*<<< orphan*/  bf_desc; TYPE_1__ bf_state; } ;

/* Variables and functions */
 int HAL_TXDESC_NOACK ; 
 int /*<<< orphan*/  ath_buf_set_rate (struct ath_softc*,struct ieee80211_node*,struct ath_buf*) ; 
 int /*<<< orphan*/  ath_hal_setupxtxdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ath_tx_is_11n (struct ath_softc*) ; 

__attribute__((used)) static void
ath_tx_set_ratectrl(struct ath_softc *sc, struct ieee80211_node *ni,
    struct ath_buf *bf)
{
	struct ath_rc_series *rc = bf->bf_state.bfs_rc;

	/* If mrr is disabled, blank tries 1, 2, 3 */
	if (! bf->bf_state.bfs_ismrr)
		rc[1].tries = rc[2].tries = rc[3].tries = 0;

#if 0
	/*
	 * If NOACK is set, just set ntries=1.
	 */
	else if (bf->bf_state.bfs_txflags & HAL_TXDESC_NOACK) {
		rc[1].tries = rc[2].tries = rc[3].tries = 0;
		rc[0].tries = 1;
	}
#endif

	/*
	 * Always call - that way a retried descriptor will
	 * have the MRR fields overwritten.
	 *
	 * XXX TODO: see if this is really needed - setting up
	 * the first descriptor should set the MRR fields to 0
	 * for us anyway.
	 */
	if (ath_tx_is_11n(sc)) {
		ath_buf_set_rate(sc, ni, bf);
	} else {
		ath_hal_setupxtxdesc(sc->sc_ah, bf->bf_desc
			, rc[1].ratecode, rc[1].tries
			, rc[2].ratecode, rc[2].tries
			, rc[3].ratecode, rc[3].tries
		);
	}
}