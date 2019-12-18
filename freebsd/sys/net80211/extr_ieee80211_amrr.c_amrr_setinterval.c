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
struct ieee80211vap {struct ieee80211_amrr* iv_rs; } ;
struct ieee80211_amrr {int /*<<< orphan*/  amrr_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_ticks (int) ; 

__attribute__((used)) static void
amrr_setinterval(const struct ieee80211vap *vap, int msecs)
{
	struct ieee80211_amrr *amrr = vap->iv_rs;

	if (!amrr)
		return;

	if (msecs < 100)
		msecs = 100;
	amrr->amrr_interval = msecs_to_ticks(msecs);
}