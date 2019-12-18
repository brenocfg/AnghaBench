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
struct ieee80211com {int dummy; } ;
struct ieee80211_channel {int ic_flags; int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 int IEEE80211_CHAN_VHT ; 
 struct ieee80211_channel* ieee80211_find_channel (struct ieee80211com*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ieee80211_channel *
findvhtchan(struct ieee80211com *ic, struct ieee80211_channel *c, int vhtflags)
{

	return (ieee80211_find_channel(ic, c->ic_freq,
	    (c->ic_flags & ~IEEE80211_CHAN_VHT) | vhtflags));
}