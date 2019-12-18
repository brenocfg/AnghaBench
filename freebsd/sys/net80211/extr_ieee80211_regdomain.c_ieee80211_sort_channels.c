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
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sort_channels (struct ieee80211_channel*,int,int) ; 

void
ieee80211_sort_channels(struct ieee80211_channel chans[], int nchans)
{
	if (nchans > 0)
		sort_channels(chans, nchans, sizeof(struct ieee80211_channel));
}