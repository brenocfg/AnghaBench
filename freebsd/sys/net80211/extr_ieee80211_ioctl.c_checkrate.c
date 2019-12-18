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
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */
 int IEEE80211_FIXED_RATE_NONE ; 
 int IEEE80211_RATE_VAL ; 

__attribute__((used)) static int
checkrate(const struct ieee80211_rateset *rs, int rate)
{
	int i;

	if (rate == IEEE80211_FIXED_RATE_NONE)
		return 1;
	for (i = 0; i < rs->rs_nrates; i++)
		if ((rs->rs_rates[i] & IEEE80211_RATE_VAL) == rate)
			return 1;
	return 0;
}