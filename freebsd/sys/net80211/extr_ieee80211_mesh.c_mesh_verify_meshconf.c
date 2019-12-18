#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_meshconf_ie {scalar_t__ conf_pselid; scalar_t__ conf_pmetid; scalar_t__ conf_ccid; scalar_t__ conf_syncid; scalar_t__ conf_authid; int conf_cap; } ;
struct ieee80211_mesh_state {TYPE_2__* ms_pmetric; TYPE_1__* ms_ppath; } ;
struct TYPE_4__ {scalar_t__ mpm_ie; } ;
struct TYPE_3__ {scalar_t__ mpp_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int /*<<< orphan*/ ,char*,int) ; 
 int IEEE80211_MESHCONF_CAP_AP ; 
 scalar_t__ IEEE80211_MESHCONF_SYNC_NEIGHOFF ; 
 int /*<<< orphan*/  IEEE80211_MSG_MESH ; 

__attribute__((used)) static int
mesh_verify_meshconf(struct ieee80211vap *vap, const uint8_t *ie)
{
	const struct ieee80211_meshconf_ie *meshconf =
	    (const struct ieee80211_meshconf_ie *) ie;
	const struct ieee80211_mesh_state *ms = vap->iv_mesh;

	if (meshconf == NULL)
		return 1;
	if (meshconf->conf_pselid != ms->ms_ppath->mpp_ie) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "unknown path selection algorithm: 0x%x\n",
		    meshconf->conf_pselid);
		return 1;
	}
	if (meshconf->conf_pmetid != ms->ms_pmetric->mpm_ie) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "unknown path metric algorithm: 0x%x\n",
		    meshconf->conf_pmetid);
		return 1;
	}
	if (meshconf->conf_ccid != 0) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "unknown congestion control algorithm: 0x%x\n",
		    meshconf->conf_ccid);
		return 1;
	}
	if (meshconf->conf_syncid != IEEE80211_MESHCONF_SYNC_NEIGHOFF) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "unknown sync algorithm: 0x%x\n",
		    meshconf->conf_syncid);
		return 1;
	}
	if (meshconf->conf_authid != 0) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "unknown auth auth algorithm: 0x%x\n",
		    meshconf->conf_pselid);
		return 1;
	}
	/* Not accepting peers */
	if (!(meshconf->conf_cap & IEEE80211_MESHCONF_CAP_AP)) {
		IEEE80211_DPRINTF(vap, IEEE80211_MSG_MESH,
		    "not accepting peers: 0x%x\n", meshconf->conf_cap);
		return 1;
	}
	return 0;
}