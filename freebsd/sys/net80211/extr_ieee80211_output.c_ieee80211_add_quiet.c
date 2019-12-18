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
struct ieee80211vap {int iv_quiet_count_value; int iv_quiet_count; int /*<<< orphan*/  iv_quiet_offset; int /*<<< orphan*/  iv_quiet_duration; int /*<<< orphan*/  iv_quiet_period; } ;
struct ieee80211_quiet_ie {int len; int tbttcount; void* offset; void* duration; int /*<<< orphan*/  period; int /*<<< orphan*/  quiet_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_QUIET ; 
 void* htole16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *
ieee80211_add_quiet(uint8_t *frm, struct ieee80211vap *vap, int update)
{
	struct ieee80211_quiet_ie *quiet = (struct ieee80211_quiet_ie *) frm;

	quiet->quiet_ie = IEEE80211_ELEMID_QUIET;
	quiet->len = 6;

	/*
	 * Only update every beacon interval - otherwise probe responses
	 * would update the quiet count value.
	 */
	if (update) {
		if (vap->iv_quiet_count_value == 1)
			vap->iv_quiet_count_value = vap->iv_quiet_count;
		else if (vap->iv_quiet_count_value > 1)
			vap->iv_quiet_count_value--;
	}

	if (vap->iv_quiet_count_value == 0) {
		/* value 0 is reserved as per 802.11h standerd */
		vap->iv_quiet_count_value = 1;
	}

	quiet->tbttcount = vap->iv_quiet_count_value;
	quiet->period = vap->iv_quiet_period;
	quiet->duration = htole16(vap->iv_quiet_duration);
	quiet->offset = htole16(vap->iv_quiet_offset);
	return frm + sizeof(*quiet);
}