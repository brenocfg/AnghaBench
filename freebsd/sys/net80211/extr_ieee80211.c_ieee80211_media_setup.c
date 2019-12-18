#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifmedia {int dummy; } ;
struct ieee80211com {int ic_txstream; int ic_htcaps; int /*<<< orphan*/  ic_modecaps; struct ieee80211_rateset* ic_sup_rates; } ;
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;
typedef  int /*<<< orphan*/  ifm_stat_cb_t ;
typedef  int /*<<< orphan*/  ifm_change_cb_t ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;
typedef  int /*<<< orphan*/  allrates ;
struct TYPE_2__ {int ht40_rate_400ns; int ht40_rate_800ns; int ht20_rate_400ns; int ht20_rate_800ns; } ;

/* Variables and functions */
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_AUTO ; 
 int IEEE80211_MODE_VHT_5GHZ ; 
 int IEEE80211_RATE_VAL ; 
 int IFM_AUTO ; 
 int IFM_IEEE80211_MCS ; 
 int IFM_IEEE80211_VHT ; 
 int IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  addmedia (struct ifmedia*,int,int,int,int) ; 
 TYPE_1__* ieee80211_htrates ; 
 int ieee80211_rate2media (struct ieee80211com*,int,int) ; 
 int /*<<< orphan*/  ifmedia_init (struct ifmedia*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isclr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rateset*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_media_setup(struct ieee80211com *ic,
	struct ifmedia *media, int caps, int addsta,
	ifm_change_cb_t media_change, ifm_stat_cb_t media_stat)
{
	int i, j, rate, maxrate, mword, r;
	enum ieee80211_phymode mode;
	const struct ieee80211_rateset *rs;
	struct ieee80211_rateset allrates;

	/*
	 * Fill in media characteristics.
	 */
	ifmedia_init(media, 0, media_change, media_stat);
	maxrate = 0;
	/*
	 * Add media for legacy operating modes.
	 */
	memset(&allrates, 0, sizeof(allrates));
	for (mode = IEEE80211_MODE_AUTO; mode < IEEE80211_MODE_11NA; mode++) {
		if (isclr(ic->ic_modecaps, mode))
			continue;
		addmedia(media, caps, addsta, mode, IFM_AUTO);
		if (mode == IEEE80211_MODE_AUTO)
			continue;
		rs = &ic->ic_sup_rates[mode];
		for (i = 0; i < rs->rs_nrates; i++) {
			rate = rs->rs_rates[i];
			mword = ieee80211_rate2media(ic, rate, mode);
			if (mword == 0)
				continue;
			addmedia(media, caps, addsta, mode, mword);
			/*
			 * Add legacy rate to the collection of all rates.
			 */
			r = rate & IEEE80211_RATE_VAL;
			for (j = 0; j < allrates.rs_nrates; j++)
				if (allrates.rs_rates[j] == r)
					break;
			if (j == allrates.rs_nrates) {
				/* unique, add to the set */
				allrates.rs_rates[j] = r;
				allrates.rs_nrates++;
			}
			rate = (rate & IEEE80211_RATE_VAL) / 2;
			if (rate > maxrate)
				maxrate = rate;
		}
	}
	for (i = 0; i < allrates.rs_nrates; i++) {
		mword = ieee80211_rate2media(ic, allrates.rs_rates[i],
				IEEE80211_MODE_AUTO);
		if (mword == 0)
			continue;
		/* NB: remove media options from mword */
		addmedia(media, caps, addsta,
		    IEEE80211_MODE_AUTO, IFM_SUBTYPE(mword));
	}
	/*
	 * Add HT/11n media.  Note that we do not have enough
	 * bits in the media subtype to express the MCS so we
	 * use a "placeholder" media subtype and any fixed MCS
	 * must be specified with a different mechanism.
	 */
	for (; mode <= IEEE80211_MODE_11NG; mode++) {
		if (isclr(ic->ic_modecaps, mode))
			continue;
		addmedia(media, caps, addsta, mode, IFM_AUTO);
		addmedia(media, caps, addsta, mode, IFM_IEEE80211_MCS);
	}
	if (isset(ic->ic_modecaps, IEEE80211_MODE_11NA) ||
	    isset(ic->ic_modecaps, IEEE80211_MODE_11NG)) {
		addmedia(media, caps, addsta,
		    IEEE80211_MODE_AUTO, IFM_IEEE80211_MCS);
		i = ic->ic_txstream * 8 - 1;
		if ((ic->ic_htcaps & IEEE80211_HTCAP_CHWIDTH40) &&
		    (ic->ic_htcaps & IEEE80211_HTCAP_SHORTGI40))
			rate = ieee80211_htrates[i].ht40_rate_400ns;
		else if ((ic->ic_htcaps & IEEE80211_HTCAP_CHWIDTH40))
			rate = ieee80211_htrates[i].ht40_rate_800ns;
		else if ((ic->ic_htcaps & IEEE80211_HTCAP_SHORTGI20))
			rate = ieee80211_htrates[i].ht20_rate_400ns;
		else
			rate = ieee80211_htrates[i].ht20_rate_800ns;
		if (rate > maxrate)
			maxrate = rate;
	}

	/*
	 * Add VHT media.
	 */
	for (; mode <= IEEE80211_MODE_VHT_5GHZ; mode++) {
		if (isclr(ic->ic_modecaps, mode))
			continue;
		addmedia(media, caps, addsta, mode, IFM_AUTO);
		addmedia(media, caps, addsta, mode, IFM_IEEE80211_VHT);

		/* XXX TODO: VHT maxrate */
	}

	return maxrate;
}