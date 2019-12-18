#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mwl_hal_channel {int /*<<< orphan*/  maxTxPow; int /*<<< orphan*/  ieee; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_3__ {int nchannels; struct mwl_hal_channel* channels; } ;
typedef  TYPE_1__ MWL_HAL_CHANNELINFO ;

/* Variables and functions */
 int ENOENT ; 
 int ieee80211_add_channel_ht40 (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
addht40channels(struct ieee80211_channel chans[], int maxchans, int *nchans,
	const MWL_HAL_CHANNELINFO *ci, int flags)
{
	int i, error;

	for (i = 0; i < ci->nchannels; i++) {
		const struct mwl_hal_channel *hc = &ci->channels[i];

		error = ieee80211_add_channel_ht40(chans, maxchans, nchans,
		    hc->ieee, hc->maxTxPow, flags);
		if (error != 0 && error != ENOENT)
			break;
	}
}