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
struct ieee80211_scan_state {scalar_t__ ss_nssid; int ss_flags; } ;
struct ieee80211_channel {int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_PASSIVE ; 
 int IEEE80211_SCAN_ACTIVE ; 
 int IWI_SCAN_TYPE_BDIRECTED ; 
 int IWI_SCAN_TYPE_BROADCAST ; 
 int IWI_SCAN_TYPE_PASSIVE ; 

__attribute__((used)) static int
scan_type(const struct ieee80211_scan_state *ss,
	const struct ieee80211_channel *chan)
{
	/* We can only set one essid for a directed scan */
	if (ss->ss_nssid != 0)
		return IWI_SCAN_TYPE_BDIRECTED;
	if ((ss->ss_flags & IEEE80211_SCAN_ACTIVE) &&
	    (chan->ic_flags & IEEE80211_CHAN_PASSIVE) == 0)
		return IWI_SCAN_TYPE_BROADCAST;
	return IWI_SCAN_TYPE_PASSIVE;
}