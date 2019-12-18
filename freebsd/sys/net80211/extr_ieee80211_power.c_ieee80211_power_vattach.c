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
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/  iv_sta_ps; int /*<<< orphan*/  iv_node_ps; int /*<<< orphan*/  iv_set_tim; int /*<<< orphan*/  iv_update_ps; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  ieee80211_node_pwrsave ; 
 int /*<<< orphan*/  ieee80211_set_tim ; 
 int /*<<< orphan*/  ieee80211_sta_pwrsave ; 
 int /*<<< orphan*/  ieee80211_update_ps ; 

void
ieee80211_power_vattach(struct ieee80211vap *vap)
{
	if (vap->iv_opmode == IEEE80211_M_HOSTAP ||
	    vap->iv_opmode == IEEE80211_M_IBSS) {
		/* NB: driver should override */
		vap->iv_update_ps = ieee80211_update_ps;
		vap->iv_set_tim = ieee80211_set_tim;
	}
	vap->iv_node_ps = ieee80211_node_pwrsave;
	vap->iv_sta_ps = ieee80211_sta_pwrsave;
}