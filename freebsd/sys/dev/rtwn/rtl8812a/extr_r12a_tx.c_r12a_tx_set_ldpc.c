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
struct r12a_tx_desc {int /*<<< orphan*/  txdw5; } ;
struct ieee80211vap {int iv_flags_ht; } ;
struct ieee80211_node {int ni_htcap; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_FHT_LDPC_TX ; 
 int IEEE80211_HTCAP_LDPC ; 
 int /*<<< orphan*/  R12A_TXDW5_DATA_LDPC ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r12a_tx_set_ldpc(struct rtwn_softc *sc, struct r12a_tx_desc *txd,
    struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;

	if ((vap->iv_flags_ht & IEEE80211_FHT_LDPC_TX) &&
	    (ni->ni_htcap & IEEE80211_HTCAP_LDPC))
		txd->txdw5 |= htole32(R12A_TXDW5_DATA_LDPC);
}