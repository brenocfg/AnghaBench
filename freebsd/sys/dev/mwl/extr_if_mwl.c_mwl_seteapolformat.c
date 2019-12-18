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
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_vap {int /*<<< orphan*/  mv_eapolformat; } ;
struct ieee80211vap {scalar_t__ iv_state; int iv_flags_ht; TYPE_1__* iv_txparms; struct ieee80211_node* iv_bss; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_chan; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;
struct TYPE_2__ {int /*<<< orphan*/  mgmtrate; } ;

/* Variables and functions */
 int IEEE80211_FHT_PUREN ; 
 size_t IEEE80211_MODE_11A ; 
 size_t IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct mwl_vap* MWL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int ieee80211_chan2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_calcformat (int /*<<< orphan*/ ,struct ieee80211_node*) ; 

__attribute__((used)) static void
mwl_seteapolformat(struct ieee80211vap *vap)
{
	struct mwl_vap *mvp = MWL_VAP(vap);
	struct ieee80211_node *ni = vap->iv_bss;
	enum ieee80211_phymode mode;
	uint8_t rate;

	KASSERT(vap->iv_state == IEEE80211_S_RUN, ("state %d", vap->iv_state));

	mode = ieee80211_chan2mode(ni->ni_chan);
	/*
	 * Use legacy rates when operating a mixed HT+non-HT bss.
	 * NB: this may violate POLA for sta and wds vap's.
	 */
	if (mode == IEEE80211_MODE_11NA &&
	    (vap->iv_flags_ht & IEEE80211_FHT_PUREN) == 0)
		rate = vap->iv_txparms[IEEE80211_MODE_11A].mgmtrate;
	else if (mode == IEEE80211_MODE_11NG &&
	    (vap->iv_flags_ht & IEEE80211_FHT_PUREN) == 0)
		rate = vap->iv_txparms[IEEE80211_MODE_11G].mgmtrate;
	else
		rate = vap->iv_txparms[mode].mgmtrate;

	mvp->mv_eapolformat = htole16(mwl_calcformat(rate, ni));
}