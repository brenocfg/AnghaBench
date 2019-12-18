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
struct ieee80211vap {scalar_t__ iv_opmode; int iv_caps; int /*<<< orphan*/  iv_opdetach; int /*<<< orphan*/  iv_recv_ctl; int /*<<< orphan*/  iv_recv_mgmt; int /*<<< orphan*/  iv_input; int /*<<< orphan*/  iv_newstate; } ;

/* Variables and functions */
 int IEEE80211_C_TDMA ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  adhoc_input ; 
 int /*<<< orphan*/  adhoc_newstate ; 
 int /*<<< orphan*/  adhoc_recv_ctl ; 
 int /*<<< orphan*/  adhoc_recv_mgmt ; 
 int /*<<< orphan*/  adhoc_vdetach ; 
 int /*<<< orphan*/  ahdemo_recv_mgmt ; 
 int /*<<< orphan*/  ieee80211_tdma_vattach (struct ieee80211vap*) ; 

__attribute__((used)) static void
adhoc_vattach(struct ieee80211vap *vap)
{
	vap->iv_newstate = adhoc_newstate;
	vap->iv_input = adhoc_input;
	if (vap->iv_opmode == IEEE80211_M_IBSS)
		vap->iv_recv_mgmt = adhoc_recv_mgmt;
	else
		vap->iv_recv_mgmt = ahdemo_recv_mgmt;
	vap->iv_recv_ctl = adhoc_recv_ctl;
	vap->iv_opdetach = adhoc_vdetach;
#ifdef IEEE80211_SUPPORT_TDMA
	/*
	 * Throw control to tdma support.  Note we do this
	 * after setting up our callbacks so it can piggyback
	 * on top of us.
	 */
	if (vap->iv_caps & IEEE80211_C_TDMA)
		ieee80211_tdma_vattach(vap);
#endif
}