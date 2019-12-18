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
struct ieee80211com {int ic_htcaps; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int /*<<< orphan*/  ht_rateprint (struct ieee80211com*,int,int) ; 
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*,char const*) ; 
 char** ieee80211_phymode_name ; 

__attribute__((used)) static void
ht_announce(struct ieee80211com *ic, enum ieee80211_phymode mode)
{
	const char *modestr = ieee80211_phymode_name[mode];

	ic_printf(ic, "%s MCS 20MHz\n", modestr);
	ht_rateprint(ic, mode, 0);
	if (ic->ic_htcaps & IEEE80211_HTCAP_SHORTGI20) {
		ic_printf(ic, "%s MCS 20MHz SGI\n", modestr);
		ht_rateprint(ic, mode, 1);
	}
	if (ic->ic_htcaps & IEEE80211_HTCAP_CHWIDTH40) {
		ic_printf(ic, "%s MCS 40MHz:\n", modestr);
		ht_rateprint(ic, mode, 2);
	}
	if ((ic->ic_htcaps & IEEE80211_HTCAP_CHWIDTH40) &&
	    (ic->ic_htcaps & IEEE80211_HTCAP_SHORTGI40)) {
		ic_printf(ic, "%s MCS 40MHz SGI:\n", modestr);
		ht_rateprint(ic, mode, 3);
	}
}