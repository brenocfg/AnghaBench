#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int* rs_rates; } ;
struct ieee80211_rssadapt_node {int** ra_rate_thresh; int ra_rix; int /*<<< orphan*/  ra_last_raise; TYPE_2__ ra_rates; TYPE_1__* ra_rs; } ;
struct TYPE_6__ {int /*<<< orphan*/  rc_decay; } ;
struct TYPE_4__ {int /*<<< orphan*/  vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  IEEE80211_MSG_RATECTL ; 
 int IEEE80211_RATE_SIZE ; 
 int IEEE80211_RATE_VAL ; 
 size_t bucket (int) ; 
 int interpolate (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__ master_expavgctl ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static void
rssadapt_raise_rate(struct ieee80211_rssadapt_node *ra, int pktlen, int rssi)
{
	uint16_t (*thrs)[IEEE80211_RATE_SIZE];
	uint16_t newthr, oldthr;
	int rix;

	thrs = &ra->ra_rate_thresh[bucket(pktlen)];

	rix = ra->ra_rix;
	if ((*thrs)[rix + 1] > (*thrs)[rix]) {
		oldthr = (*thrs)[rix + 1];
		if ((*thrs)[rix] == 0)
			newthr = (rssi << 8);
		else
			newthr = (*thrs)[rix];
		(*thrs)[rix + 1] = interpolate(master_expavgctl.rc_decay,
		    oldthr, newthr);

		IEEE80211_DPRINTF(ra->ra_rs->vap, IEEE80211_MSG_RATECTL,
		    "RSSADAPT raise threshold for rate %d (oldthr %d newthr %d rssi %d)\n",
		    ra->ra_rates.rs_rates[rix + 1] & IEEE80211_RATE_VAL,
		    oldthr, newthr, rssi);

		ra->ra_last_raise = ticks;
	}
}