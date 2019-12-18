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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct uath_softc {struct ieee80211com sc_ic; } ;
struct uath_cmd_set_associd {int /*<<< orphan*/  bssid; void* timoffset; void* associd; void* defaultrateix; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; } ;
struct ieee80211_node {int ni_associd; int /*<<< orphan*/  ni_bssid; } ;
typedef  int /*<<< orphan*/  associd ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WDCMSG_WRITE_ASSOCID ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uath_cmd_set_associd*,int /*<<< orphan*/ ,int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,struct uath_cmd_set_associd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_write_associd(struct uath_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	struct ieee80211_node *ni;
	struct uath_cmd_set_associd associd;

	ni = ieee80211_ref_node(vap->iv_bss);
	memset(&associd, 0, sizeof(associd));
	associd.defaultrateix = htobe32(1);	/* XXX */
	associd.associd = htobe32(ni->ni_associd);
	associd.timoffset = htobe32(0x3b);	/* XXX */
	IEEE80211_ADDR_COPY(associd.bssid, ni->ni_bssid);
	ieee80211_free_node(ni);
	return uath_cmd_write(sc, WDCMSG_WRITE_ASSOCID, &associd,
	    sizeof associd, 0);
}