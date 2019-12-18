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
struct iwi_softc {int dummy; } ;
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ifmediareq {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct iwi_softc* ic_softc; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_txrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWI_CSR_CURRENT_TX_RATE ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_media_status (struct ifnet*,struct ifmediareq*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_cvtrate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_media_status(struct ifnet *ifp, struct ifmediareq *imr)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	struct iwi_softc *sc = ic->ic_softc;
	struct ieee80211_node *ni;

	/* read current transmission rate from adapter */
	ni = ieee80211_ref_node(vap->iv_bss);
	ni->ni_txrate =
	    iwi_cvtrate(CSR_READ_4(sc, IWI_CSR_CURRENT_TX_RATE));
	ieee80211_free_node(ni);
	ieee80211_media_status(ifp, imr);
}