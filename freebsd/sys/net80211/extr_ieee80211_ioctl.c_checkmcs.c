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
struct ieee80211_htrateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */
 int IEEE80211_FIXED_RATE_NONE ; 
 int IEEE80211_RATE_MCS ; 
 int IEEE80211_RV (int) ; 

__attribute__((used)) static int
checkmcs(const struct ieee80211_htrateset *rs, int mcs)
{
	int rate_val = IEEE80211_RV(mcs);
	int i;

	if (mcs == IEEE80211_FIXED_RATE_NONE)
		return 1;
	if ((mcs & IEEE80211_RATE_MCS) == 0)	/* MCS always have 0x80 set */
		return 0;
	for (i = 0; i < rs->rs_nrates; i++)
		if (IEEE80211_RV(rs->rs_rates[i]) == rate_val)
			return 1;
	return 0;
}