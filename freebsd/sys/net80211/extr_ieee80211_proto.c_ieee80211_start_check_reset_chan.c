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
struct ieee80211vap {scalar_t__ iv_opmode; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_NOADHOC (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_NOHOSTAP (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 

__attribute__((used)) static int
ieee80211_start_check_reset_chan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	if ((vap->iv_opmode == IEEE80211_M_IBSS &&
	     IEEE80211_IS_CHAN_NOADHOC(ic->ic_curchan)) ||
	    (vap->iv_opmode == IEEE80211_M_HOSTAP &&
	     IEEE80211_IS_CHAN_NOHOSTAP(ic->ic_curchan)))
		return (1);
	return (0);
}