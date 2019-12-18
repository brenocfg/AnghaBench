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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  wme_hipri_switch_hysteresis; } ;
struct ieee80211com {int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_send_mgmt; TYPE_1__ ic_wme; int /*<<< orphan*/  ic_restart_task; int /*<<< orphan*/  ic_chw_task; int /*<<< orphan*/  ic_bmiss_task; int /*<<< orphan*/  ic_chan_task; int /*<<< orphan*/  ic_promisc_task; int /*<<< orphan*/  ic_mcast_task; int /*<<< orphan*/  ic_parent_task; int /*<<< orphan*/  ic_protmode; scalar_t__ ic_headroom; } ;
struct ieee80211_qosframe_addr4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGGRESSIVE_MODE_SWITCH_HYSTERESIS ; 
 scalar_t__ ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  IEEE80211_PROT_CTSONLY ; 
 scalar_t__ IEEE80211_WEP_EXTIVLEN ; 
 scalar_t__ IEEE80211_WEP_IVLEN ; 
 scalar_t__ IEEE80211_WEP_KIDLEN ; 
 scalar_t__ MHLEN ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211com*) ; 
 int /*<<< orphan*/  beacon_miss ; 
 int /*<<< orphan*/  ieee80211_adhoc_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_hostap_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_mesh_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_monitor_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_send_mgmt ; 
 int /*<<< orphan*/  ieee80211_sta_attach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_wds_attach (struct ieee80211com*) ; 
 scalar_t__ max_datalen ; 
 scalar_t__ max_hdr ; 
 scalar_t__ max_linkhdr ; 
 scalar_t__ max_protohdr ; 
 int /*<<< orphan*/  null_raw_xmit ; 
 int /*<<< orphan*/  parent_updown ; 
 int /*<<< orphan*/  restart_vaps ; 
 int /*<<< orphan*/  update_channel ; 
 int /*<<< orphan*/  update_chw ; 
 int /*<<< orphan*/  update_mcast ; 
 int /*<<< orphan*/  update_promisc ; 

void
ieee80211_proto_attach(struct ieee80211com *ic)
{
	uint8_t hdrlen;

	/* override the 802.3 setting */
	hdrlen = ic->ic_headroom
		+ sizeof(struct ieee80211_qosframe_addr4)
		+ IEEE80211_WEP_IVLEN + IEEE80211_WEP_KIDLEN
		+ IEEE80211_WEP_EXTIVLEN;
	/* XXX no way to recalculate on ifdetach */
	if (ALIGN(hdrlen) > max_linkhdr) {
		/* XXX sanity check... */
		max_linkhdr = ALIGN(hdrlen);
		max_hdr = max_linkhdr + max_protohdr;
		max_datalen = MHLEN - max_hdr;
	}
	ic->ic_protmode = IEEE80211_PROT_CTSONLY;

	TASK_INIT(&ic->ic_parent_task, 0, parent_updown, ic);
	TASK_INIT(&ic->ic_mcast_task, 0, update_mcast, ic);
	TASK_INIT(&ic->ic_promisc_task, 0, update_promisc, ic);
	TASK_INIT(&ic->ic_chan_task, 0, update_channel, ic);
	TASK_INIT(&ic->ic_bmiss_task, 0, beacon_miss, ic);
	TASK_INIT(&ic->ic_chw_task, 0, update_chw, ic);
	TASK_INIT(&ic->ic_restart_task, 0, restart_vaps, ic);

	ic->ic_wme.wme_hipri_switch_hysteresis =
		AGGRESSIVE_MODE_SWITCH_HYSTERESIS;

	/* initialize management frame handlers */
	ic->ic_send_mgmt = ieee80211_send_mgmt;
	ic->ic_raw_xmit = null_raw_xmit;

	ieee80211_adhoc_attach(ic);
	ieee80211_sta_attach(ic);
	ieee80211_wds_attach(ic);
	ieee80211_hostap_attach(ic);
#ifdef IEEE80211_SUPPORT_MESH
	ieee80211_mesh_attach(ic);
#endif
	ieee80211_monitor_attach(ic);
}