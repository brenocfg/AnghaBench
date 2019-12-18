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
struct ieee80211_channel {int ic_flags; scalar_t__ ic_extieee; scalar_t__ ic_ieee; } ;

/* Variables and functions */
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 

__attribute__((used)) static __inline void
set_extchan(struct ieee80211_channel *c)
{

	/*
	 * IEEE Std 802.11-2012, page 1738, subclause 20.3.15.4:
	 * "the secondary channel number shall be 'N + [1,-1] * 4'
	 */
	if (c->ic_flags & IEEE80211_CHAN_HT40U)
		c->ic_extieee = c->ic_ieee + 4;
	else if (c->ic_flags & IEEE80211_CHAN_HT40D)
		c->ic_extieee = c->ic_ieee - 4;
	else
		c->ic_extieee = 0;
}