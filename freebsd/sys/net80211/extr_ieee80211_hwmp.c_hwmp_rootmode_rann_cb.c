#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  is_hwmp_rootrann; } ;
struct ieee80211vap {TYPE_1__ iv_stats; int /*<<< orphan*/  iv_myaddr; int /*<<< orphan*/  iv_bss; struct ieee80211_mesh_state* iv_mesh; struct ieee80211_hwmp_state* iv_hwmp; } ;
struct ieee80211_meshrann_ie {int rann_flags; int /*<<< orphan*/  rann_metric; int /*<<< orphan*/  rann_interval; scalar_t__ rann_seq; int /*<<< orphan*/  rann_addr; int /*<<< orphan*/  rann_ttl; scalar_t__ rann_hopcount; } ;
struct ieee80211_mesh_state {int ms_flags; int /*<<< orphan*/  ms_ttl; } ;
struct ieee80211_hwmp_state {scalar_t__ hs_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MESHFLAGS_GATE ; 
 int /*<<< orphan*/  IEEE80211_MESHLMETRIC_INITIALVAL ; 
 int /*<<< orphan*/  IEEE80211_MSG_HWMP ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  broadcastaddr ; 
 int /*<<< orphan*/  hwmp_rootmode_setup (struct ieee80211vap*) ; 
 int /*<<< orphan*/  hwmp_send_rann (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_meshrann_ie*) ; 
 int /*<<< orphan*/  ieee80211_hwmp_rannint ; 

__attribute__((used)) static void
hwmp_rootmode_rann_cb(void *arg)
{
	struct ieee80211vap *vap = (struct ieee80211vap *)arg;
	struct ieee80211_hwmp_state *hs = vap->iv_hwmp;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_meshrann_ie rann;

	IEEE80211_NOTE(vap, IEEE80211_MSG_HWMP, vap->iv_bss,
	    "%s", "send broadcast RANN");

	rann.rann_flags = 0;
	if (ms->ms_flags & IEEE80211_MESHFLAGS_GATE)
		rann.rann_flags |= IEEE80211_MESHFLAGS_GATE;
	rann.rann_hopcount = 0;
	rann.rann_ttl = ms->ms_ttl;
	IEEE80211_ADDR_COPY(rann.rann_addr, vap->iv_myaddr);
	rann.rann_seq = ++hs->hs_seq;
	rann.rann_interval = ieee80211_hwmp_rannint;
	rann.rann_metric = IEEE80211_MESHLMETRIC_INITIALVAL;

	vap->iv_stats.is_hwmp_rootrann++;
	hwmp_send_rann(vap, broadcastaddr, &rann);
	hwmp_rootmode_setup(vap);
}