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
struct rtwn_softc {int dummy; } ;
struct r92c_tx_desc {int /*<<< orphan*/  txdw5; } ;
struct ieee80211vap {int iv_flags_ht; } ;
struct ieee80211_node {int ni_htcap; scalar_t__ ni_chan; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_CHAN_ANYC ; 
 int IEEE80211_FHT_SHORTGI20 ; 
 int IEEE80211_FHT_SHORTGI40 ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (scalar_t__) ; 
 int /*<<< orphan*/  R92C_TXDW5_SGI ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r92c_tx_set_sgi(struct rtwn_softc *sc, void *buf, struct ieee80211_node *ni)
{
	struct r92c_tx_desc *txd = (struct r92c_tx_desc *)buf;
	struct ieee80211vap *vap = ni->ni_vap;

	if ((vap->iv_flags_ht & IEEE80211_FHT_SHORTGI20) &&	/* HT20 */
	    (ni->ni_htcap & IEEE80211_HTCAP_SHORTGI20))
		txd->txdw5 |= htole32(R92C_TXDW5_SGI);
	else if (ni->ni_chan != IEEE80211_CHAN_ANYC &&		/* HT40 */
	    IEEE80211_IS_CHAN_HT40(ni->ni_chan) &&
	    (ni->ni_htcap & IEEE80211_HTCAP_SHORTGI40) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_SHORTGI40))
		txd->txdw5 |= htole32(R92C_TXDW5_SGI);
}