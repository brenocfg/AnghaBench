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
struct ieee80211vap {int /*<<< orphan*/  iv_bss; int /*<<< orphan*/  iv_myaddr; struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_meshgann_ie {scalar_t__ gann_seq; int /*<<< orphan*/  gann_interval; int /*<<< orphan*/  gann_addr; int /*<<< orphan*/  gann_ttl; scalar_t__ gann_hopcount; scalar_t__ gann_flags; } ;
struct ieee80211_mesh_state {int /*<<< orphan*/  ms_gateseq; int /*<<< orphan*/  ms_ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_MESH ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESH_GANN ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MSG_MESH ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_mesh_gateint ; 
 int /*<<< orphan*/  ieee80211_send_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_meshgann_ie*) ; 
 int /*<<< orphan*/  mesh_gatemode_setup (struct ieee80211vap*) ; 

__attribute__((used)) static void
mesh_gatemode_cb(void *arg)
{
	struct ieee80211vap *vap = (struct ieee80211vap *)arg;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_meshgann_ie gann;

	gann.gann_flags = 0; /* Reserved */
	gann.gann_hopcount = 0;
	gann.gann_ttl = ms->ms_ttl;
	IEEE80211_ADDR_COPY(gann.gann_addr, vap->iv_myaddr);
	gann.gann_seq = ms->ms_gateseq++;
	gann.gann_interval = ieee80211_mesh_gateint;

	IEEE80211_NOTE(vap, IEEE80211_MSG_MESH, vap->iv_bss,
	    "send broadcast GANN (seq %u)", gann.gann_seq);

	ieee80211_send_action(vap->iv_bss, IEEE80211_ACTION_CAT_MESH,
	    IEEE80211_ACTION_MESH_GANN, &gann);
	mesh_gatemode_setup(vap);
}