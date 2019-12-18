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
typedef  size_t u_int ;
struct ieee80211_channel {int ic_ieee; int ic_flags; } ;
struct TYPE_2__ {size_t ic_nchans; struct ieee80211_channel* ic_chans; } ;

/* Variables and functions */
 TYPE_1__* chaninfo ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 size_t promote (size_t) ; 

__attribute__((used)) static void
mapchan(struct ieee80211_channel *chan, int ieee, int flags)
{
	u_int i;

	for (i = 0; i < chaninfo->ic_nchans; i++) {
		const struct ieee80211_channel *c = &chaninfo->ic_chans[i];

		if (c->ic_ieee == ieee && (c->ic_flags & flags) == flags) {
			if (flags == 0) {
				/* when ambiguous promote to ``best'' */
				c = &chaninfo->ic_chans[promote(i)];
			}
			*chan = *c;
			return;
		}
	}
	errx(1, "unknown/undefined channel number %d flags 0x%x", ieee, flags);
}