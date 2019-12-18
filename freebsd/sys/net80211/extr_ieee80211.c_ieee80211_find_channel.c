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
struct ieee80211com {int /*<<< orphan*/  ic_nchans; int /*<<< orphan*/  ic_channels; struct ieee80211_channel* ic_prevchan; } ;
struct ieee80211_channel {int ic_freq; int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_ALLTURBO ; 
 struct ieee80211_channel* findchannel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

struct ieee80211_channel *
ieee80211_find_channel(struct ieee80211com *ic, int freq, int flags)
{
	struct ieee80211_channel *c;

	flags &= IEEE80211_CHAN_ALLTURBO;
	c = ic->ic_prevchan;
	if (c != NULL && c->ic_freq == freq &&
	    (c->ic_flags & IEEE80211_CHAN_ALLTURBO) == flags)
		return c;
	/* brute force search */
	return (findchannel(ic->ic_channels, ic->ic_nchans, freq, flags));
}