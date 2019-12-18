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
struct ieee80211vap {struct ieee80211_rssadapt* iv_rs; } ;
struct ieee80211_rssadapt {int /*<<< orphan*/  interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_ticks (int) ; 

__attribute__((used)) static void
rssadapt_setinterval(const struct ieee80211vap *vap, int msecs)
{
	struct ieee80211_rssadapt *rs = vap->iv_rs;

	if (!rs)
		return;

	if (msecs < 100)
		msecs = 100;
	rs->interval = msecs_to_ticks(msecs);
}