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
typedef  scalar_t__ uint8_t ;
struct ieee80211_htrateset {int rs_nrates; int* rs_rates; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; struct ieee80211_htrateset ni_htrates; } ;
struct ieee80211_ie_htinfo {int /*<<< orphan*/  hi_basicmcsset; } ;

/* Variables and functions */
 scalar_t__ const IEEE80211_ELEMID_VENDOR ; 
 int IEEE80211_HTRATE_MAXSIZE ; 
 int IEEE80211_MSG_11N ; 
 int IEEE80211_MSG_XRATE ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int,struct ieee80211_node*,char*,char*) ; 
 int IEEE80211_RATE_BASIC ; 
 int IEEE80211_RATE_VAL ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 

void
ieee80211_setup_basic_htrates(struct ieee80211_node *ni, const uint8_t *ie)
{
	const struct ieee80211_ie_htinfo *htinfo;
	struct ieee80211_htrateset *rs;
	int i, j;

	if (ie[0] == IEEE80211_ELEMID_VENDOR)
		ie += 4;
	htinfo = (const struct ieee80211_ie_htinfo *) ie;
	rs = &ni->ni_htrates;
	if (rs->rs_nrates == 0) {
		IEEE80211_NOTE(ni->ni_vap,
		    IEEE80211_MSG_XRATE | IEEE80211_MSG_11N, ni,
		    "%s", "WARNING, empty HT rate set");
		return;
	}
	for (i = 0; i < IEEE80211_HTRATE_MAXSIZE; i++) {
		if (isclr(htinfo->hi_basicmcsset, i))
			continue;
		for (j = 0; j < rs->rs_nrates; j++)
			if ((rs->rs_rates[j] & IEEE80211_RATE_VAL) == i)
				rs->rs_rates[j] |= IEEE80211_RATE_BASIC;
	}
}