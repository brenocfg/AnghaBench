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
struct ieee80211vap {scalar_t__ iv_opmode; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
ieee80211_update_ps(struct ieee80211vap *vap, int nsta)
{

	KASSERT(vap->iv_opmode == IEEE80211_M_HOSTAP ||
		vap->iv_opmode == IEEE80211_M_IBSS,
		("operating mode %u", vap->iv_opmode));
}