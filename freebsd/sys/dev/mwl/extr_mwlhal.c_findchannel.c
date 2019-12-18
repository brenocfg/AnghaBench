#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int nchannels; struct mwl_hal_channel* channels; } ;
struct mwl_hal_priv {TYPE_2__ mh_20M_5G; TYPE_2__ mh_40M_5G; TYPE_2__ mh_20M; TYPE_2__ mh_40M; } ;
struct mwl_hal_channel {int ieee; } ;
struct TYPE_5__ {scalar_t__ FreqBand; scalar_t__ ChnlWidth; scalar_t__ ExtChnlOffset; } ;
struct TYPE_7__ {int channel; TYPE_1__ channelFlags; } ;
typedef  TYPE_2__ MWL_HAL_CHANNELINFO ;
typedef  TYPE_3__ MWL_HAL_CHANNEL ;

/* Variables and functions */
 scalar_t__ MWL_CH_40_MHz_WIDTH ; 
 scalar_t__ MWL_EXT_CH_BELOW_CTRL_CH ; 
 scalar_t__ MWL_FREQ_BAND_2DOT4GHZ ; 
 scalar_t__ MWL_FREQ_BAND_5GHZ ; 

__attribute__((used)) static const struct mwl_hal_channel *
findchannel(const struct mwl_hal_priv *mh, const MWL_HAL_CHANNEL *c)
{
	const struct mwl_hal_channel *hc;
	const MWL_HAL_CHANNELINFO *ci;
	int chan = c->channel, i;

	if (c->channelFlags.FreqBand == MWL_FREQ_BAND_2DOT4GHZ) {
		i = chan - 1;
		if (c->channelFlags.ChnlWidth == MWL_CH_40_MHz_WIDTH) {
			ci = &mh->mh_40M;
			if (c->channelFlags.ExtChnlOffset == MWL_EXT_CH_BELOW_CTRL_CH)
				i -= 4;
		} else
			ci = &mh->mh_20M;
		/* 2.4G channel table is directly indexed */
		hc = ((unsigned)i < ci->nchannels) ? &ci->channels[i] : NULL;
	} else if (c->channelFlags.FreqBand == MWL_FREQ_BAND_5GHZ) {
		if (c->channelFlags.ChnlWidth == MWL_CH_40_MHz_WIDTH) {
			ci = &mh->mh_40M_5G;
			if (c->channelFlags.ExtChnlOffset == MWL_EXT_CH_BELOW_CTRL_CH)
				chan -= 4;
		} else
			ci = &mh->mh_20M_5G;
		/* 5GHz channel table is sparse and must be searched */
		for (i = 0; i < ci->nchannels; i++)
			if (ci->channels[i].ieee == chan)
				break;
		hc = (i < ci->nchannels) ? &ci->channels[i] : NULL;
	} else
		hc = NULL;
	return hc;
}