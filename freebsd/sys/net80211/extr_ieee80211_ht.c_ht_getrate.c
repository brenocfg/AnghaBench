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
struct ieee80211com {int dummy; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;
struct TYPE_2__ {int ht20_rate_800ns; int ht20_rate_400ns; int ht40_rate_800ns; int ht40_rate_400ns; } ;

/* Variables and functions */
 int IEEE80211_RATE_MCS ; 
 scalar_t__ IFM_IEEE80211_MCS ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 TYPE_1__* ieee80211_htrates ; 
 int ieee80211_rate2media (struct ieee80211com*,int,int) ; 

__attribute__((used)) static int
ht_getrate(struct ieee80211com *ic, int index, enum ieee80211_phymode mode,
    int ratetype)
{
	int mword, rate;

	mword = ieee80211_rate2media(ic, index | IEEE80211_RATE_MCS, mode);
	if (IFM_SUBTYPE(mword) != IFM_IEEE80211_MCS)
		return (0);
	switch (ratetype) {
	case 0:
		rate = ieee80211_htrates[index].ht20_rate_800ns;
		break;
	case 1:
		rate = ieee80211_htrates[index].ht20_rate_400ns;
		break;
	case 2:
		rate = ieee80211_htrates[index].ht40_rate_800ns;
		break;
	default:
		rate = ieee80211_htrates[index].ht40_rate_400ns;
		break;
	}
	return (rate);
}