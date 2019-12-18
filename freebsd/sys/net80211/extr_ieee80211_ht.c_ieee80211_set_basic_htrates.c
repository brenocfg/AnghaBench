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
struct ieee80211_htrateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */
 int IEEE80211_HTRATE_MAXSIZE ; 
 int IEEE80211_RATE_BASIC ; 
 int IEEE80211_RATE_VAL ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ieee80211_set_basic_htrates(uint8_t *frm, const struct ieee80211_htrateset *rs)
{
	int i;

	for (i = 0; i < rs->rs_nrates; i++) {
		int r = rs->rs_rates[i] & IEEE80211_RATE_VAL;
		if ((rs->rs_rates[i] & IEEE80211_RATE_BASIC) &&
		    r < IEEE80211_HTRATE_MAXSIZE) {
			/* NB: this assumes a particular implementation */
			setbit(frm, r);
		}
	}
}