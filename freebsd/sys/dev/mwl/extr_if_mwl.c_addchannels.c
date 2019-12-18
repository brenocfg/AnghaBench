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
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_hal_channel {int /*<<< orphan*/  maxTxPow; int /*<<< orphan*/  freq; int /*<<< orphan*/  ieee; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_3__ {int nchannels; struct mwl_hal_channel* channels; } ;
typedef  TYPE_1__ MWL_HAL_CHANNELINFO ;

/* Variables and functions */
 int ieee80211_add_channel (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
addchannels(struct ieee80211_channel chans[], int maxchans, int *nchans,
	const MWL_HAL_CHANNELINFO *ci, const uint8_t bands[])
{
	int i, error;

	error = 0;
	for (i = 0; i < ci->nchannels && error == 0; i++) {
		const struct mwl_hal_channel *hc = &ci->channels[i];

		error = ieee80211_add_channel(chans, maxchans, nchans,
		    hc->ieee, hc->freq, hc->maxTxPow, 0, bands);
	}
}