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
struct ieee80211_channel {scalar_t__ ic_freq; int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_ALL ; 

__attribute__((used)) static __inline int
chancompar(const void *a, const void *b)
{
	const struct ieee80211_channel *ca = a;
	const struct ieee80211_channel *cb = b;

	return (ca->ic_freq == cb->ic_freq) ?
		(ca->ic_flags & IEEE80211_CHAN_ALL) -
		    (cb->ic_flags & IEEE80211_CHAN_ALL) :
		ca->ic_freq - cb->ic_freq;
}