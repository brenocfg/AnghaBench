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
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; struct ieee80211_hwmp_state* iv_hwmp; } ;
struct ieee80211_mesh_state {int /*<<< orphan*/  ms_flags; } ;
struct ieee80211_hwmp_state {int hs_rootmode; int /*<<< orphan*/  hs_roottimer; } ;

/* Variables and functions */
#define  IEEE80211_HWMP_ROOTMODE_DISABLED 131 
#define  IEEE80211_HWMP_ROOTMODE_NORMAL 130 
#define  IEEE80211_HWMP_ROOTMODE_PROACTIVE 129 
#define  IEEE80211_HWMP_ROOTMODE_RANN 128 
 int /*<<< orphan*/  IEEE80211_MESHFLAGS_ROOT ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int /*<<< orphan*/  hwmp_rootmode_cb ; 
 int /*<<< orphan*/  hwmp_rootmode_rann_cb ; 
 int /*<<< orphan*/  ieee80211_hwmp_rannint ; 
 int /*<<< orphan*/  ieee80211_hwmp_rootint ; 

__attribute__((used)) static void
hwmp_rootmode_setup(struct ieee80211vap *vap)
{
	struct ieee80211_hwmp_state *hs = vap->iv_hwmp;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;

	switch (hs->hs_rootmode) {
	case IEEE80211_HWMP_ROOTMODE_DISABLED:
		callout_drain(&hs->hs_roottimer);
		ms->ms_flags &= ~IEEE80211_MESHFLAGS_ROOT;
		break;
	case IEEE80211_HWMP_ROOTMODE_NORMAL:
	case IEEE80211_HWMP_ROOTMODE_PROACTIVE:
		callout_reset(&hs->hs_roottimer, ieee80211_hwmp_rootint,
		    hwmp_rootmode_cb, vap);
		ms->ms_flags |= IEEE80211_MESHFLAGS_ROOT;
		break;
	case IEEE80211_HWMP_ROOTMODE_RANN:
		callout_reset(&hs->hs_roottimer, ieee80211_hwmp_rannint,
		    hwmp_rootmode_rann_cb, vap);
		ms->ms_flags |= IEEE80211_MESHFLAGS_ROOT;
		break;
	}
}