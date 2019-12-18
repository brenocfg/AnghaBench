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
struct ural_vap {int /*<<< orphan*/  ratectl_ch; struct ieee80211vap vap; } ;
struct ieee80211_ratectl_tx_stats {int nsuccess; int nframes; int nretries; int /*<<< orphan*/  flags; } ;
struct ural_softc {int* sta; struct ieee80211_ratectl_tx_stats sc_txs; } ;
struct TYPE_2__ {struct ural_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RATECTL_TX_STATS_RETRIES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_STA_CSR0 ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_ratectl_tx_update (struct ieee80211vap*,struct ieee80211_ratectl_tx_stats*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ural_ratectl_timeout ; 
 int /*<<< orphan*/  ural_read_multi (struct ural_softc*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ural_vap*) ; 

__attribute__((used)) static void
ural_ratectl_task(void *arg, int pending)
{
	struct ural_vap *uvp = arg;
	struct ieee80211vap *vap = &uvp->vap;
	struct ural_softc *sc = vap->iv_ic->ic_softc;
	struct ieee80211_ratectl_tx_stats *txs = &sc->sc_txs;
	int fail;

	RAL_LOCK(sc);
	/* read and clear statistic registers (STA_CSR0 to STA_CSR10) */
	ural_read_multi(sc, RAL_STA_CSR0, sc->sta, sizeof(sc->sta));

	txs->flags = IEEE80211_RATECTL_TX_STATS_RETRIES;
	txs->nsuccess = sc->sta[7] +	/* TX ok w/o retry */
			sc->sta[8];	/* TX ok w/ retry */
	fail = sc->sta[9];		/* TX retry-fail count */
	txs->nframes = txs->nsuccess + fail;
	/* XXX fail * maxretry */
	txs->nretries = sc->sta[8] + fail;

	ieee80211_ratectl_tx_update(vap, txs);

	/* count TX retry-fail as Tx errors */
	if_inc_counter(vap->iv_ifp, IFCOUNTER_OERRORS, fail);

	usb_callout_reset(&uvp->ratectl_ch, hz, ural_ratectl_timeout, uvp);
	RAL_UNLOCK(sc);
}