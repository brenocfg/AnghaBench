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
struct ieee80211_roamparam {int rssi; int rate; } ;
struct TYPE_2__ {struct ieee80211_roamparam* params; } ;

/* Variables and functions */
 int IEEE80211_MODE_11A ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_MAX ; 
 int IEEE80211_MODE_VHT_2GHZ ; 
 int IEEE80211_MODE_VHT_5GHZ ; 
 int IEEE80211_RATE_MCS ; 
 int /*<<< orphan*/  LINE_CHECK (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  getroam (int) ; 
 int /*<<< orphan*/ * modename ; 
 TYPE_1__ roamparams ; 

__attribute__((used)) static void
list_roam(int s)
{
	const struct ieee80211_roamparam *rp;
	int mode;

	getroam(s);
	for (mode = IEEE80211_MODE_11A; mode < IEEE80211_MODE_MAX; mode++) {
		rp = &roamparams.params[mode];
		if (rp->rssi == 0 && rp->rate == 0)
			continue;
		if (mode == IEEE80211_MODE_11NA ||
		    mode == IEEE80211_MODE_11NG ||
		    mode == IEEE80211_MODE_VHT_2GHZ ||
		    mode == IEEE80211_MODE_VHT_5GHZ) {
			if (rp->rssi & 1)
				LINE_CHECK("roam:%-7.7s rssi %2u.5dBm  MCS %2u    ",
				    modename[mode], rp->rssi/2,
				    rp->rate &~ IEEE80211_RATE_MCS);
			else
				LINE_CHECK("roam:%-7.7s rssi %4udBm  MCS %2u    ",
				    modename[mode], rp->rssi/2,
				    rp->rate &~ IEEE80211_RATE_MCS);
		} else {
			if (rp->rssi & 1)
				LINE_CHECK("roam:%-7.7s rssi %2u.5dBm rate %2u Mb/s",
				    modename[mode], rp->rssi/2, rp->rate/2);
			else
				LINE_CHECK("roam:%-7.7s rssi %4udBm rate %2u Mb/s",
				    modename[mode], rp->rssi/2, rp->rate/2);
		}
	}
}