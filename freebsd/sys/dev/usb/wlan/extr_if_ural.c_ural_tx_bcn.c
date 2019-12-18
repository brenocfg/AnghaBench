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
struct ural_tx_data {int /*<<< orphan*/  desc; int /*<<< orphan*/  rate; struct ieee80211_node* ni; struct mbuf* m; } ;
struct ural_softc {scalar_t__ tx_nfree; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  tx_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ieee80211vap {struct ieee80211_txparam* iv_txparms; } ;
struct ieee80211com {scalar_t__ ic_bsschan; } ;
struct ieee80211_txparam {int /*<<< orphan*/  mgmtrate; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENXIO ; 
 scalar_t__ IEEE80211_CHAN_ANYC ; 
 int RAL_TX_IFS_NEWBACKOFF ; 
 int RAL_TX_TIMESTAMP ; 
 struct ural_tx_data* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ural_tx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t URAL_BULK_WR ; 
 size_t ieee80211_chan2mode (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ural_setup_tx_desc (struct ural_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ural_tx_bcn(struct ural_softc *sc, struct mbuf *m0, struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211com *ic = ni->ni_ic;
	const struct ieee80211_txparam *tp;
	struct ural_tx_data *data;

	if (sc->tx_nfree == 0) {
		m_freem(m0);
		ieee80211_free_node(ni);
		return (EIO);
	}
	if (ic->ic_bsschan == IEEE80211_CHAN_ANYC) {
		m_freem(m0);
		ieee80211_free_node(ni);
		return (ENXIO);
	}
	data = STAILQ_FIRST(&sc->tx_free);
	STAILQ_REMOVE_HEAD(&sc->tx_free, next);
	sc->tx_nfree--;
	tp = &vap->iv_txparms[ieee80211_chan2mode(ic->ic_bsschan)];

	data->m = m0;
	data->ni = ni;
	data->rate = tp->mgmtrate;

	ural_setup_tx_desc(sc, &data->desc,
	    RAL_TX_IFS_NEWBACKOFF | RAL_TX_TIMESTAMP, m0->m_pkthdr.len,
	    tp->mgmtrate);

	DPRINTFN(10, "sending beacon frame len=%u rate=%u\n",
	    m0->m_pkthdr.len, tp->mgmtrate);

	STAILQ_INSERT_TAIL(&sc->tx_q, data, next);
	usbd_transfer_start(sc->sc_xfer[URAL_BULK_WR]);

	return (0);
}