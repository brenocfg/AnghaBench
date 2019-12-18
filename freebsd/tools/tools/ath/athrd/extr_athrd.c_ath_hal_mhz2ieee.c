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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_A ; 
 scalar_t__ IS_CHAN_IN_PUBLIC_SAFETY_BAND (int) ; 
 int mappsb (int,int) ; 

int
ath_hal_mhz2ieee(struct ath_hal *ah, u_int freq, u_int flags)
{
	if (flags & IEEE80211_CHAN_2GHZ) {	/* 2GHz band */
		if (freq == 2484)
			return 14;
		if (freq < 2484)
			return ((int)freq - 2407) / 5;
		else
			return 15 + ((freq - 2512) / 20);
	} else if (flags & IEEE80211_CHAN_5GHZ) {/* 5Ghz band */
		if (IS_CHAN_IN_PUBLIC_SAFETY_BAND(freq))
			return mappsb(freq, flags);
		else if ((flags & IEEE80211_CHAN_A) && (freq <= 5000))
			return (freq - 4000) / 5;
		else
			return (freq - 5000) / 5;
	} else {			/* either, guess */
		if (freq == 2484)
			return 14;
		if (freq < 2484)
			return ((int)freq - 2407) / 5;
		if (freq < 5000) {
			if (IS_CHAN_IN_PUBLIC_SAFETY_BAND(freq))
				return mappsb(freq, flags);
			else if (freq > 4900)
				return (freq - 4000) / 5;
			else
				return 15 + ((freq - 2512) / 20);
		}
		return (freq - 5000) / 5;
	}
}