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
struct ieee80211com {int ic_curmode; int /*<<< orphan*/ * ic_sup_rates; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 int IEEE80211_MODE_11B ; 
 int IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  ieee80211_reset_erp (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_setbasicrates (int /*<<< orphan*/ *,int) ; 

int
ieee80211_setmode(struct ieee80211com *ic, enum ieee80211_phymode mode)
{
	/*
	 * Adjust basic rates in 11b/11g supported rate set.
	 * Note that if operating on a hal/quarter rate channel
	 * this is a noop as those rates sets are different
	 * and used instead.
	 */
	if (mode == IEEE80211_MODE_11G || mode == IEEE80211_MODE_11B)
		ieee80211_setbasicrates(&ic->ic_sup_rates[mode], mode);

	ic->ic_curmode = mode;
	ieee80211_reset_erp(ic);	/* reset ERP state */

	return 0;
}