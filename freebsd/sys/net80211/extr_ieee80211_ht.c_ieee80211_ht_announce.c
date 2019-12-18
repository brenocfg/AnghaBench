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
struct ieee80211com {int /*<<< orphan*/  ic_modecaps; int /*<<< orphan*/  ic_rxstream; int /*<<< orphan*/  ic_txstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MODE_11NA ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 int /*<<< orphan*/  ht_announce (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ieee80211_ht_announce(struct ieee80211com *ic)
{

	if (isset(ic->ic_modecaps, IEEE80211_MODE_11NA) ||
	    isset(ic->ic_modecaps, IEEE80211_MODE_11NG))
		ic_printf(ic, "%dT%dR\n", ic->ic_txstream, ic->ic_rxstream);
	if (isset(ic->ic_modecaps, IEEE80211_MODE_11NA))
		ht_announce(ic, IEEE80211_MODE_11NA);
	if (isset(ic->ic_modecaps, IEEE80211_MODE_11NG))
		ht_announce(ic, IEEE80211_MODE_11NG);
}