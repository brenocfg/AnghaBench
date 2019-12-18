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
struct ieee80211vap {int /*<<< orphan*/  iv_ifp; TYPE_1__* iv_ic; } ;
struct rum_vap {int maxretry; int /*<<< orphan*/  ratectl_ch; struct ieee80211vap vap; } ;
struct ieee80211_ratectl_tx_stats {int nframes; int nsuccess; int nretries; int /*<<< orphan*/  flags; } ;
struct rum_softc {int /*<<< orphan*/ * sta; struct ieee80211_ratectl_tx_stats sc_txs; } ;
struct TYPE_2__ {struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RATECTL_TX_STATS_RETRIES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  RT2573_STA_CSR0 ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_ratectl_tx_update (struct ieee80211vap*,struct ieee80211_ratectl_tx_stats*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_ratectl_timeout ; 
 int /*<<< orphan*/  rum_read_multi (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rum_vap*) ; 

__attribute__((used)) static void
rum_ratectl_task(void *arg, int pending)
{
	struct rum_vap *rvp = arg;
	struct ieee80211vap *vap = &rvp->vap;
	struct rum_softc *sc = vap->iv_ic->ic_softc;
	struct ieee80211_ratectl_tx_stats *txs = &sc->sc_txs;
	int ok[3], fail;

	RUM_LOCK(sc);
	/* read and clear statistic registers (STA_CSR0 to STA_CSR5) */
	rum_read_multi(sc, RT2573_STA_CSR0, sc->sta, sizeof(sc->sta));

	ok[0] = (le32toh(sc->sta[4]) & 0xffff);	/* TX ok w/o retry */
	ok[1] = (le32toh(sc->sta[4]) >> 16);	/* TX ok w/ one retry */
	ok[2] = (le32toh(sc->sta[5]) & 0xffff);	/* TX ok w/ multiple retries */
	fail =  (le32toh(sc->sta[5]) >> 16);	/* TX retry-fail count */

	txs->flags = IEEE80211_RATECTL_TX_STATS_RETRIES;
	txs->nframes = ok[0] + ok[1] + ok[2] + fail;
	txs->nsuccess = txs->nframes - fail;
	/* XXX at least */
	txs->nretries = ok[1] + ok[2] * 2 + fail * (rvp->maxretry + 1);

	if (txs->nframes != 0)
		ieee80211_ratectl_tx_update(vap, txs);

	/* count TX retry-fail as Tx errors */
	if_inc_counter(vap->iv_ifp, IFCOUNTER_OERRORS, fail);

	usb_callout_reset(&rvp->ratectl_ch, hz, rum_ratectl_timeout, rvp);
	RUM_UNLOCK(sc);
}