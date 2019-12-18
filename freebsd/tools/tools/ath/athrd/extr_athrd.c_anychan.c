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
anychan(const struct ieee80211_channel *chans, int nc, int flag)
{
	int i;

	for (i = 0; i < nc; i++)
		if ((chans[i].ic_flags & flag) != 0)
			return 1;
	return 0;
}