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
typedef  int u_int ;

/* Variables and functions */
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_GSM ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_QUARTER ; 

u_int
ieee80211_ieee2mhz(u_int chan, u_int flags)
{
	if (flags & IEEE80211_CHAN_GSM)
		return 907 + 5 * (chan / 10);
	if (flags & IEEE80211_CHAN_2GHZ) {	/* 2GHz band */
		if (chan == 14)
			return 2484;
		if (chan < 14)
			return 2407 + chan*5;
		else
			return 2512 + ((chan-15)*20);
	} else if (flags & IEEE80211_CHAN_5GHZ) {/* 5Ghz band */
		if (flags & (IEEE80211_CHAN_HALF|IEEE80211_CHAN_QUARTER)) {
			chan -= 37;
			return 4940 + chan*5 + (chan % 5 ? 2 : 0);
		}
		return 5000 + (chan*5);
	} else {				/* either, guess */
		/* XXX can't distinguish PSB+GSM channels */
		if (chan == 14)
			return 2484;
		if (chan < 14)			/* 0-13 */
			return 2407 + chan*5;
		if (chan < 27)			/* 15-26 */
			return 2512 + ((chan-15)*20);
		return 5000 + (chan*5);
	}
}