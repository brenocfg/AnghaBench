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
struct mwl_softc {int /*<<< orphan*/  sc_mh; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  bands ;
typedef  int /*<<< orphan*/  MWL_HAL_CHANNELINFO ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_HTA ; 
 int /*<<< orphan*/  IEEE80211_CHAN_HTG ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NA ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/  MWL_CH_20_MHz_WIDTH ; 
 int /*<<< orphan*/  MWL_CH_40_MHz_WIDTH ; 
 int /*<<< orphan*/  MWL_FREQ_BAND_2DOT4GHZ ; 
 int /*<<< orphan*/  MWL_FREQ_BAND_5GHZ ; 
 int /*<<< orphan*/  addchannels (struct ieee80211_channel*,int,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addht40channels (struct ieee80211_channel*,int,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mwl_hal_getchannelinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getchannels(struct mwl_softc *sc, int maxchans, int *nchans,
	struct ieee80211_channel chans[])
{
	const MWL_HAL_CHANNELINFO *ci;
	uint8_t bands[IEEE80211_MODE_BYTES];

	/*
	 * Use the channel info from the hal to craft the
	 * channel list.  Note that we pass back an unsorted
	 * list; the caller is required to sort it for us
	 * (if desired).
	 */
	*nchans = 0;
	if (mwl_hal_getchannelinfo(sc->sc_mh,
	    MWL_FREQ_BAND_2DOT4GHZ, MWL_CH_20_MHz_WIDTH, &ci) == 0) {
		memset(bands, 0, sizeof(bands));
		setbit(bands, IEEE80211_MODE_11B);
		setbit(bands, IEEE80211_MODE_11G);
		setbit(bands, IEEE80211_MODE_11NG);
		addchannels(chans, maxchans, nchans, ci, bands);
	}
	if (mwl_hal_getchannelinfo(sc->sc_mh,
	    MWL_FREQ_BAND_5GHZ, MWL_CH_20_MHz_WIDTH, &ci) == 0) {
		memset(bands, 0, sizeof(bands));
		setbit(bands, IEEE80211_MODE_11A);
		setbit(bands, IEEE80211_MODE_11NA);
		addchannels(chans, maxchans, nchans, ci, bands);
	}
	if (mwl_hal_getchannelinfo(sc->sc_mh,
	    MWL_FREQ_BAND_2DOT4GHZ, MWL_CH_40_MHz_WIDTH, &ci) == 0)
		addht40channels(chans, maxchans, nchans, ci, IEEE80211_CHAN_HTG);
	if (mwl_hal_getchannelinfo(sc->sc_mh,
	    MWL_FREQ_BAND_5GHZ, MWL_CH_40_MHz_WIDTH, &ci) == 0)
		addht40channels(chans, maxchans, nchans, ci, IEEE80211_CHAN_HTA);
}