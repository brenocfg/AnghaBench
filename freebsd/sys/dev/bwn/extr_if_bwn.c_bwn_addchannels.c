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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_channel {int dummy; } ;
struct bwn_channelinfo {int nchannels; struct bwn_channel* channels; } ;
struct bwn_channel {int /*<<< orphan*/  maxTxPow; int /*<<< orphan*/  freq; int /*<<< orphan*/  ieee; } ;

/* Variables and functions */
 int ieee80211_add_channel (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
bwn_addchannels(struct ieee80211_channel chans[], int maxchans, int *nchans,
    const struct bwn_channelinfo *ci, const uint8_t bands[])
{
	int i, error;

	for (i = 0, error = 0; i < ci->nchannels && error == 0; i++) {
		const struct bwn_channel *hc = &ci->channels[i];

		error = ieee80211_add_channel(chans, maxchans, nchans,
		    hc->ieee, hc->freq, hc->maxTxPow, 0, bands);
	}
}