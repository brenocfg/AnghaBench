#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct ath_softc {void* sc_lastdatarix; void* sc_txrix; } ;
struct TYPE_4__ {int bfs_try0; void* bfs_txrate0; TYPE_2__* bfs_rc; scalar_t__ bfs_ismrr; int /*<<< orphan*/  bfs_pktlen; int /*<<< orphan*/  bfs_shpream; int /*<<< orphan*/  bfs_doratelookup; } ;
struct ath_buf {TYPE_1__ bf_state; int /*<<< orphan*/  bf_node; } ;
struct TYPE_5__ {int tries; void* ratecode; void* rix; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_NODE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_NODE_UNLOCK (int /*<<< orphan*/ ) ; 
 int ATH_TXMAXTRY ; 
 int /*<<< orphan*/  ath_rate_findrate (struct ath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int*,void**) ; 
 int /*<<< orphan*/  ath_rate_getxtxrates (struct ath_softc*,int /*<<< orphan*/ ,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 

__attribute__((used)) static void
ath_tx_do_ratelookup(struct ath_softc *sc, struct ath_buf *bf)
{
	uint8_t rate, rix;
	int try0;

	if (! bf->bf_state.bfs_doratelookup)
		return;

	/* Get rid of any previous state */
	bzero(bf->bf_state.bfs_rc, sizeof(bf->bf_state.bfs_rc));

	ATH_NODE_LOCK(ATH_NODE(bf->bf_node));
	ath_rate_findrate(sc, ATH_NODE(bf->bf_node), bf->bf_state.bfs_shpream,
	    bf->bf_state.bfs_pktlen, &rix, &try0, &rate);

	/* In case MRR is disabled, make sure rc[0] is setup correctly */
	bf->bf_state.bfs_rc[0].rix = rix;
	bf->bf_state.bfs_rc[0].ratecode = rate;
	bf->bf_state.bfs_rc[0].tries = try0;

	if (bf->bf_state.bfs_ismrr && try0 != ATH_TXMAXTRY)
		ath_rate_getxtxrates(sc, ATH_NODE(bf->bf_node), rix,
		    bf->bf_state.bfs_rc);
	ATH_NODE_UNLOCK(ATH_NODE(bf->bf_node));

	sc->sc_txrix = rix;	/* for LED blinking */
	sc->sc_lastdatarix = rix;	/* for fast frames */
	bf->bf_state.bfs_try0 = try0;
	bf->bf_state.bfs_txrate0 = rate;
}