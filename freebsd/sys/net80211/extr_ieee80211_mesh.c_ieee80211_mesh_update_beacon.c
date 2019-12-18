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
struct ieee80211_beacon_offsets {int /*<<< orphan*/  bo_flags; int /*<<< orphan*/  bo_meshconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BEACON_MESHCONF ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  clrbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_add_meshconf (int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 scalar_t__ isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ieee80211_mesh_update_beacon(struct ieee80211vap *vap,
	struct ieee80211_beacon_offsets *bo)
{
	KASSERT(vap->iv_opmode == IEEE80211_M_MBSS, ("not a MBSS vap"));

	if (isset(bo->bo_flags, IEEE80211_BEACON_MESHCONF)) {
		(void)ieee80211_add_meshconf(bo->bo_meshconf, vap);
		clrbit(bo->bo_flags, IEEE80211_BEACON_MESHCONF);
	}
}