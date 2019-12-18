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
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_mesh_state {int ms_flags; int /*<<< orphan*/  ms_gatetimer; } ;

/* Variables and functions */
 int IEEE80211_MESHFLAGS_GATE ; 
 int IEEE80211_MESHFLAGS_ROOT ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_mesh_gateint ; 
 int /*<<< orphan*/  mesh_gatemode_cb ; 

__attribute__((used)) static void
mesh_gatemode_setup(struct ieee80211vap *vap)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;

	/*
	 * NB: When a mesh gate is running as a ROOT it shall
	 * not send out periodic GANNs but instead mark the
	 * mesh gate flag for the corresponding proactive PREQ
	 * and RANN frames.
	 */
	if (ms->ms_flags & IEEE80211_MESHFLAGS_ROOT ||
	    (ms->ms_flags & IEEE80211_MESHFLAGS_GATE) == 0) {
		callout_drain(&ms->ms_gatetimer);
		return ;
	}
	callout_reset(&ms->ms_gatetimer, ieee80211_mesh_gateint,
	    mesh_gatemode_cb, vap);
}