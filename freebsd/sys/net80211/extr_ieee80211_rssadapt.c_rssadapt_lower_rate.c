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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  size_t u_int ;
struct TYPE_5__ {int* rs_rates; } ;
struct ieee80211_rssadapt_node {size_t ra_rix; TYPE_2__ ra_rates; TYPE_1__* ra_rs; int /*<<< orphan*/ ** ra_rate_thresh; } ;
struct TYPE_6__ {int /*<<< orphan*/  rc_thresh; } ;
struct TYPE_4__ {int /*<<< orphan*/  vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_MSG_RATECTL ; 
 int IEEE80211_RATE_SIZE ; 
 int IEEE80211_RATE_VAL ; 
 size_t bucket (int) ; 
 int /*<<< orphan*/  interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ master_expavgctl ; 

__attribute__((used)) static void
rssadapt_lower_rate(struct ieee80211_rssadapt_node *ra, int pktlen, int rssi)
{
	uint16_t last_thr;
	uint16_t (*thrs)[IEEE80211_RATE_SIZE];
	u_int rix;

	thrs = &ra->ra_rate_thresh[bucket(pktlen)];

	rix = ra->ra_rix;
	last_thr = (*thrs)[rix];
	(*thrs)[rix] = interpolate(master_expavgctl.rc_thresh,
	    last_thr, (rssi << 8));

	IEEE80211_DPRINTF(ra->ra_rs->vap, IEEE80211_MSG_RATECTL,
	    "RSSADAPT lower threshold for rate %d (last_thr %d new thr %d rssi %d)\n",
	    ra->ra_rates.rs_rates[rix + 1] & IEEE80211_RATE_VAL,
	    last_thr, (*thrs)[rix], rssi);
}