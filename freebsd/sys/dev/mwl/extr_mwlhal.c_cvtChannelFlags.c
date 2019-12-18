#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ FreqBand; int ChnlWidth; int ExtChnlOffset; } ;
struct TYPE_5__ {TYPE_1__ channelFlags; } ;
typedef  TYPE_2__ MWL_HAL_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  CH_10_MHz_WIDTH ; 
 int /*<<< orphan*/  CH_20_MHz_WIDTH ; 
 int /*<<< orphan*/  CH_40_MHz_WIDTH ; 
 int /*<<< orphan*/  EXT_CH_ABOVE_CTRL_CH ; 
 int /*<<< orphan*/  EXT_CH_BELOW_CTRL_CH ; 
 int /*<<< orphan*/  EXT_CH_NONE ; 
 int /*<<< orphan*/  FREQ_BAND_2DOT4GHZ ; 
 int /*<<< orphan*/  FREQ_BAND_5GHZ ; 
#define  MWL_CH_10_MHz_WIDTH 133 
#define  MWL_CH_20_MHz_WIDTH 132 
#define  MWL_CH_40_MHz_WIDTH 131 
#define  MWL_EXT_CH_ABOVE_CTRL_CH 130 
#define  MWL_EXT_CH_BELOW_CTRL_CH 129 
#define  MWL_EXT_CH_NONE 128 
 scalar_t__ MWL_FREQ_BAND_2DOT4GHZ ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
cvtChannelFlags(const MWL_HAL_CHANNEL *chan)
{
	uint32_t w;

	/*
	 * NB: f/w only understands FREQ_BAND_5GHZ, supplying the more
	 *     precise band info causes it to lockup (sometimes).
	 */
	w = (chan->channelFlags.FreqBand == MWL_FREQ_BAND_2DOT4GHZ) ?
		FREQ_BAND_2DOT4GHZ : FREQ_BAND_5GHZ;
	switch (chan->channelFlags.ChnlWidth) {
	case MWL_CH_10_MHz_WIDTH:
		w |= CH_10_MHz_WIDTH;
		break;
	case MWL_CH_20_MHz_WIDTH:
		w |= CH_20_MHz_WIDTH;
		break;
	case MWL_CH_40_MHz_WIDTH:
	default:
		w |= CH_40_MHz_WIDTH;
		break;
	}
	switch (chan->channelFlags.ExtChnlOffset) {
	case MWL_EXT_CH_NONE:
		w |= EXT_CH_NONE;
		break;
	case MWL_EXT_CH_ABOVE_CTRL_CH:
		w |= EXT_CH_ABOVE_CTRL_CH;
		break;
	case MWL_EXT_CH_BELOW_CTRL_CH:
		w |= EXT_CH_BELOW_CTRL_CH;
		break;
	}
	return htole32(w);
}