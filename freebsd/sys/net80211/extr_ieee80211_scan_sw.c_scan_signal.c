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
struct ieee80211com {int dummy; } ;
struct ieee80211_scan_state {struct ieee80211com* ss_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  scan_signal_locked (struct ieee80211_scan_state*,int) ; 

__attribute__((used)) static void
scan_signal(struct ieee80211_scan_state *ss, int iflags)
{
	struct ieee80211com *ic = ss->ss_ic;

	IEEE80211_UNLOCK_ASSERT(ic);

	IEEE80211_LOCK(ic);
	scan_signal_locked(ss, iflags);
	IEEE80211_UNLOCK(ic);
}