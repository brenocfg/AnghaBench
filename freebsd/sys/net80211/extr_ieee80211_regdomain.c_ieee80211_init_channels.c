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
struct ieee80211_regdomain {scalar_t__ ecm; } ;
struct ieee80211com {int ic_nchans; int ic_htcaps; struct ieee80211_regdomain ic_regdomain; struct ieee80211_channel* ic_channels; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NA ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 int /*<<< orphan*/  def_chan_2ghz ; 
 int /*<<< orphan*/  def_chan_5ghz_band1 ; 
 int /*<<< orphan*/  def_chan_5ghz_band2 ; 
 int /*<<< orphan*/  def_chan_5ghz_band3 ; 
 int /*<<< orphan*/  ieee80211_add_channel_list_2ghz (struct ieee80211_channel*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ieee80211_add_channel_list_5ghz (struct ieee80211_channel*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ isset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ ) ; 

int
ieee80211_init_channels(struct ieee80211com *ic,
	const struct ieee80211_regdomain *rd, const uint8_t bands[])
{
	struct ieee80211_channel *chans = ic->ic_channels;
	int *nchans = &ic->ic_nchans;
	int ht40;

	/* XXX just do something for now */
	ht40 = !!(ic->ic_htcaps & IEEE80211_HTCAP_CHWIDTH40);
	*nchans = 0;
	if (isset(bands, IEEE80211_MODE_11B) ||
	    isset(bands, IEEE80211_MODE_11G) ||
	    isset(bands, IEEE80211_MODE_11NG)) {
		int nchan = nitems(def_chan_2ghz);
		if (!(rd != NULL && rd->ecm))
			nchan -= 3;

		ieee80211_add_channel_list_2ghz(chans, IEEE80211_CHAN_MAX,
		    nchans, def_chan_2ghz, nchan, bands, ht40);
	}
	if (isset(bands, IEEE80211_MODE_11A) ||
	    isset(bands, IEEE80211_MODE_11NA)) {
		ieee80211_add_channel_list_5ghz(chans, IEEE80211_CHAN_MAX,
		    nchans, def_chan_5ghz_band1, nitems(def_chan_5ghz_band1),
		    bands, ht40);
		ieee80211_add_channel_list_5ghz(chans, IEEE80211_CHAN_MAX,
		    nchans, def_chan_5ghz_band2, nitems(def_chan_5ghz_band2),
		    bands, ht40);
		ieee80211_add_channel_list_5ghz(chans, IEEE80211_CHAN_MAX,
		    nchans, def_chan_5ghz_band3, nitems(def_chan_5ghz_band3),
		    bands, ht40);
	}
	if (rd != NULL)
		ic->ic_regdomain = *rd;

	return 0;
}