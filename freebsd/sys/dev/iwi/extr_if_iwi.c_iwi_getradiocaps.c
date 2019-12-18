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
struct ieee80211com {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  bands ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/  def_chan_5ghz_band1 ; 
 int /*<<< orphan*/  def_chan_5ghz_band2 ; 
 int /*<<< orphan*/  def_chan_5ghz_band3 ; 
 int /*<<< orphan*/  ieee80211_add_channel_list_5ghz (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_add_channels_default_2ghz (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_collect_bands (struct ieee80211com*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	uint8_t bands[IEEE80211_MODE_BYTES];

	iwi_collect_bands(ic, bands, sizeof(bands));
	*nchans = 0;
	if (isset(bands, IEEE80211_MODE_11B) || isset(bands, IEEE80211_MODE_11G))
		ieee80211_add_channels_default_2ghz(chans, maxchans, nchans,
		    bands, 0);
	if (isset(bands, IEEE80211_MODE_11A)) {
		ieee80211_add_channel_list_5ghz(chans, maxchans, nchans,
		    def_chan_5ghz_band1, nitems(def_chan_5ghz_band1),
		    bands, 0);
		ieee80211_add_channel_list_5ghz(chans, maxchans, nchans,
		    def_chan_5ghz_band2, nitems(def_chan_5ghz_band2),
		    bands, 0);
		ieee80211_add_channel_list_5ghz(chans, maxchans, nchans,
		    def_chan_5ghz_band3, nitems(def_chan_5ghz_band3),
		    bands, 0);
	}
}