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
struct bwn_txstatus {int /*<<< orphan*/  cookie; } ;
struct bwn_softc {scalar_t__ sc_watchdog_timer; } ;
struct bwn_pio_txqueue {int /*<<< orphan*/  tq_pktlist; int /*<<< orphan*/  tq_free; int /*<<< orphan*/  tq_used; } ;
struct bwn_pio_txpkt {TYPE_2__* tp_m; int /*<<< orphan*/ * tp_ni; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ASSERT_LOCKED (struct bwn_softc*) ; 
 scalar_t__ BWN_HDRSIZE (struct bwn_mac*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bwn_pio_txpkt*,int /*<<< orphan*/ ) ; 
 struct bwn_pio_txqueue* bwn_pio_parse_cookie (struct bwn_mac*,int /*<<< orphan*/ ,struct bwn_pio_txpkt**) ; 
 int /*<<< orphan*/  bwn_ratectl_tx_complete (int /*<<< orphan*/ *,struct bwn_txstatus const*) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  tp_list ; 

__attribute__((used)) static void
bwn_pio_handle_txeof(struct bwn_mac *mac,
    const struct bwn_txstatus *status)
{
	struct bwn_pio_txqueue *tq;
	struct bwn_pio_txpkt *tp = NULL;
	struct bwn_softc *sc = mac->mac_sc;

	BWN_ASSERT_LOCKED(sc);

	tq = bwn_pio_parse_cookie(mac, status->cookie, &tp);
	if (tq == NULL)
		return;

	tq->tq_used -= roundup(tp->tp_m->m_pkthdr.len + BWN_HDRSIZE(mac), 4);
	tq->tq_free++;

	if (tp->tp_ni != NULL) {
		/*
		 * Do any tx complete callback.  Note this must
		 * be done before releasing the node reference.
		 */
		bwn_ratectl_tx_complete(tp->tp_ni, status);
	}
	ieee80211_tx_complete(tp->tp_ni, tp->tp_m, 0);
	tp->tp_ni = NULL;
	tp->tp_m = NULL;
	TAILQ_INSERT_TAIL(&tq->tq_pktlist, tp, tp_list);

	sc->sc_watchdog_timer = 0;
}