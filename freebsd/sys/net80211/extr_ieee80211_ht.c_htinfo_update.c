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
typedef  int uint8_t ;
struct ieee80211com {scalar_t__ ic_sta_assoc; scalar_t__ ic_ht_sta_assoc; int ic_flags_ht; scalar_t__ ic_bsschan; scalar_t__ ic_ht40_sta_assoc; int ic_curhtprotmode; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_CHAN_ANYC ; 
 int IEEE80211_FHT_NONHT_PR ; 
 int IEEE80211_HTINFO_NONHT_PRESENT ; 
 int IEEE80211_HTINFO_OPMODE_HT20PR ; 
 int IEEE80211_HTINFO_OPMODE_MIXED ; 
 int IEEE80211_HTINFO_OPMODE_PROTOPT ; 
 int IEEE80211_HTINFO_OPMODE_PURE ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (scalar_t__) ; 
 int /*<<< orphan*/  htinfo_notify (struct ieee80211com*) ; 

__attribute__((used)) static void
htinfo_update(struct ieee80211com *ic)
{
	uint8_t protmode;

	if (ic->ic_sta_assoc != ic->ic_ht_sta_assoc) {
		protmode = IEEE80211_HTINFO_OPMODE_MIXED
			 | IEEE80211_HTINFO_NONHT_PRESENT;
	} else if (ic->ic_flags_ht & IEEE80211_FHT_NONHT_PR) {
		protmode = IEEE80211_HTINFO_OPMODE_PROTOPT
			 | IEEE80211_HTINFO_NONHT_PRESENT;
	} else if (ic->ic_bsschan != IEEE80211_CHAN_ANYC &&
	    IEEE80211_IS_CHAN_HT40(ic->ic_bsschan) && 
	    ic->ic_sta_assoc != ic->ic_ht40_sta_assoc) {
		protmode = IEEE80211_HTINFO_OPMODE_HT20PR;
	} else {
		protmode = IEEE80211_HTINFO_OPMODE_PURE;
	}
	if (protmode != ic->ic_curhtprotmode) {
		ic->ic_curhtprotmode = protmode;
		htinfo_notify(ic);
	}
}