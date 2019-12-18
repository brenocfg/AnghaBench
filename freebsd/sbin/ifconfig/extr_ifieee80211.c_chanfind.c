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
struct ieee80211_channel {int ic_flags; } ;

/* Variables and functions */

__attribute__((used)) static int
chanfind(const struct ieee80211_channel chans[], int nchans, int flags)
{
	int i;

	for (i = 0; i < nchans; i++) {
		const struct ieee80211_channel *c = &chans[i];
		if ((c->ic_flags & flags) == flags)
			return 1;
	}
	return 0;
}