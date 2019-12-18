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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211vap {scalar_t__ iv_opmode; struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_mesh_state {int ms_neighbors; int ms_flags; TYPE_2__* ms_pmetric; TYPE_1__* ms_ppath; } ;
struct TYPE_4__ {int /*<<< orphan*/  mpm_ie; } ;
struct TYPE_3__ {int /*<<< orphan*/  mpp_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_MESHCONF ; 
 int /*<<< orphan*/  IEEE80211_MESHCONF_AUTH_DISABLED ; 
 int /*<<< orphan*/  IEEE80211_MESHCONF_CAP_AP ; 
 int /*<<< orphan*/  IEEE80211_MESHCONF_CAP_FWRD ; 
 int /*<<< orphan*/  IEEE80211_MESHCONF_CC_DISABLED ; 
 int IEEE80211_MESHCONF_FORM_GATE ; 
 int /*<<< orphan*/  IEEE80211_MESHCONF_SYNC_NEIGHOFF ; 
 int IEEE80211_MESHFLAGS_AP ; 
 int IEEE80211_MESHFLAGS_FWD ; 
 int IEEE80211_MESHFLAGS_GATE ; 
 int /*<<< orphan*/  IEEE80211_MESH_CONF_SZ ; 
 int IEEE80211_MESH_MAX_NEIGHBORS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

uint8_t *
ieee80211_add_meshconf(uint8_t *frm, struct ieee80211vap *vap)
{
	const struct ieee80211_mesh_state *ms = vap->iv_mesh;
	uint16_t caps;

	KASSERT(vap->iv_opmode == IEEE80211_M_MBSS, ("not a MBSS vap"));

	*frm++ = IEEE80211_ELEMID_MESHCONF;
	*frm++ = IEEE80211_MESH_CONF_SZ;
	*frm++ = ms->ms_ppath->mpp_ie;		/* path selection */
	*frm++ = ms->ms_pmetric->mpm_ie;	/* link metric */
	*frm++ = IEEE80211_MESHCONF_CC_DISABLED;
	*frm++ = IEEE80211_MESHCONF_SYNC_NEIGHOFF;
	*frm++ = IEEE80211_MESHCONF_AUTH_DISABLED;
	/* NB: set the number of neighbors before the rest */
	*frm = (ms->ms_neighbors > IEEE80211_MESH_MAX_NEIGHBORS ?
	    IEEE80211_MESH_MAX_NEIGHBORS : ms->ms_neighbors) << 1;
	if (ms->ms_flags & IEEE80211_MESHFLAGS_GATE)
		*frm |= IEEE80211_MESHCONF_FORM_GATE;
	frm += 1;
	caps = 0;
	if (ms->ms_flags & IEEE80211_MESHFLAGS_AP)
		caps |= IEEE80211_MESHCONF_CAP_AP;
	if (ms->ms_flags & IEEE80211_MESHFLAGS_FWD)
		caps |= IEEE80211_MESHCONF_CAP_FWRD;
	*frm++ = caps;
	return frm;
}