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
struct ieee80211req_chaninfo {int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_chans; } ;

/* Variables and functions */
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_GSM ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_QUARTER ; 
 int REQ_FLAGS ; 
 int chanfind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * chanlookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
checkchan(const struct ieee80211req_chaninfo *avail, int freq, int flags)
{
	flags &= ~REQ_FLAGS;
	/*
	 * Check if exact channel is in the calibration table;
	 * everything below is to deal with channels that we
	 * want to include but that are not explicitly listed.
	 */
	if (chanlookup(avail->ic_chans, avail->ic_nchans, freq, flags) != NULL)
		return 1;
	if (flags & IEEE80211_CHAN_GSM) {
		/*
		 * XXX GSM frequency mapping is handled in the kernel
		 * so we cannot find them in the calibration table;
		 * just accept the channel and the kernel will reject
		 * the channel list if it's wrong.
		 */
		return 1;
	}
	/*
	 * If this is a 1/2 or 1/4 width channel allow it if a full
	 * width channel is present for this frequency, and the device
	 * supports fractional channels on this band.  This is a hack
	 * that avoids bloating the calibration table; it may be better
	 * by per-band attributes though (we are effectively calculating
	 * this attribute by scanning the channel list ourself).
	 */
	if ((flags & (IEEE80211_CHAN_HALF | IEEE80211_CHAN_QUARTER)) == 0)
		return 0;
	if (chanlookup(avail->ic_chans, avail->ic_nchans, freq,
	    flags &~ (IEEE80211_CHAN_HALF | IEEE80211_CHAN_QUARTER)) == NULL)
		return 0;
	if (flags & IEEE80211_CHAN_HALF) {
		return chanfind(avail->ic_chans, avail->ic_nchans,
		    IEEE80211_CHAN_HALF |
		       (flags & (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ)));
	} else {
		return chanfind(avail->ic_chans, avail->ic_nchans,
		    IEEE80211_CHAN_QUARTER |
			(flags & (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ)));
	}
}