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
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; int scan_interval; int network_select; int auto_network_select; scalar_t__ after_wps; scalar_t__ owe_transition_search; TYPE_1__* conf; scalar_t__ p2p_in_invitation; scalar_t__ show_group_started; scalar_t__ p2p_in_provisioning; struct wpa_ssid* current_ssid; scalar_t__ ifmsh; scalar_t__ p2p_mgmt; } ;
struct wpa_ssid {int dummy; } ;
struct wpa_bss {int dummy; } ;
struct TYPE_2__ {scalar_t__ cred; scalar_t__ interworking; scalar_t__ auto_interworking; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 scalar_t__ WPA_AUTHENTICATING ; 
 int /*<<< orphan*/  WPA_EVENT_NETWORK_NOT_FOUND ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interworking_start_fetch_anqp (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_msg_ctrl (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_associate (struct wpa_supplicant*,int /*<<< orphan*/ *,struct wpa_ssid*) ; 
 scalar_t__ wpa_supplicant_connect (struct wpa_supplicant*,struct wpa_bss*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_need_to_roam (struct wpa_supplicant*,struct wpa_bss*,struct wpa_ssid*) ; 
 struct wpa_bss* wpa_supplicant_pick_network (struct wpa_supplicant*,struct wpa_ssid**) ; 
 struct wpa_ssid* wpa_supplicant_pick_new_network (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_req_new_scan (struct wpa_supplicant*,int,int) ; 
 scalar_t__ wpa_supplicant_req_sched_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_rsn_preauth_scan_results (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_network_reenabled ; 
 int wpas_p2p_scan_no_go_seen (struct wpa_supplicant*) ; 
 int wpas_reenabled_network_time (struct wpa_supplicant*) ; 
 scalar_t__ wpas_wps_searching (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpas_select_network_from_last_scan(struct wpa_supplicant *wpa_s,
					      int new_scan, int own_request)
{
	struct wpa_bss *selected;
	struct wpa_ssid *ssid = NULL;
	int time_to_reenable = wpas_reenabled_network_time(wpa_s);

	if (time_to_reenable > 0) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"Postpone network selection by %d seconds since all networks are disabled",
			time_to_reenable);
		eloop_cancel_timeout(wpas_network_reenabled, wpa_s, NULL);
		eloop_register_timeout(time_to_reenable, 0,
				       wpas_network_reenabled, wpa_s, NULL);
		return 0;
	}

	if (wpa_s->p2p_mgmt)
		return 0; /* no normal connection on p2p_mgmt interface */

	wpa_s->owe_transition_search = 0;
	selected = wpa_supplicant_pick_network(wpa_s, &ssid);

#ifdef CONFIG_MESH
	if (wpa_s->ifmsh) {
		wpa_msg(wpa_s, MSG_INFO,
			"Avoiding join because we already joined a mesh group");
		return 0;
	}
#endif /* CONFIG_MESH */

	if (selected) {
		int skip;
		skip = !wpa_supplicant_need_to_roam(wpa_s, selected, ssid);
		if (skip) {
			if (new_scan)
				wpa_supplicant_rsn_preauth_scan_results(wpa_s);
			return 0;
		}

		if (ssid != wpa_s->current_ssid &&
		    wpa_s->wpa_state >= WPA_AUTHENTICATING) {
			wpa_s->own_disconnect_req = 1;
			wpa_supplicant_deauthenticate(
				wpa_s, WLAN_REASON_DEAUTH_LEAVING);
		}

		if (wpa_supplicant_connect(wpa_s, selected, ssid) < 0) {
			wpa_dbg(wpa_s, MSG_DEBUG, "Connect failed");
			return -1;
		}
		if (new_scan)
			wpa_supplicant_rsn_preauth_scan_results(wpa_s);
		/*
		 * Do not allow other virtual radios to trigger operations based
		 * on these scan results since we do not want them to start
		 * other associations at the same time.
		 */
		return 1;
	} else {
		wpa_dbg(wpa_s, MSG_DEBUG, "No suitable network found");
		ssid = wpa_supplicant_pick_new_network(wpa_s);
		if (ssid) {
			wpa_dbg(wpa_s, MSG_DEBUG, "Setup a new network");
			wpa_supplicant_associate(wpa_s, NULL, ssid);
			if (new_scan)
				wpa_supplicant_rsn_preauth_scan_results(wpa_s);
		} else if (own_request) {
			/*
			 * No SSID found. If SCAN results are as a result of
			 * own scan request and not due to a scan request on
			 * another shared interface, try another scan.
			 */
			int timeout_sec = wpa_s->scan_interval;
			int timeout_usec = 0;
#ifdef CONFIG_P2P
			int res;

			res = wpas_p2p_scan_no_go_seen(wpa_s);
			if (res == 2)
				return 2;
			if (res == 1)
				return 0;

			if (wpa_s->p2p_in_provisioning ||
			    wpa_s->show_group_started ||
			    wpa_s->p2p_in_invitation) {
				/*
				 * Use shorter wait during P2P Provisioning
				 * state and during P2P join-a-group operation
				 * to speed up group formation.
				 */
				timeout_sec = 0;
				timeout_usec = 250000;
				wpa_supplicant_req_new_scan(wpa_s, timeout_sec,
							    timeout_usec);
				return 0;
			}
#endif /* CONFIG_P2P */
#ifdef CONFIG_INTERWORKING
			if (wpa_s->conf->auto_interworking &&
			    wpa_s->conf->interworking &&
			    wpa_s->conf->cred) {
				wpa_dbg(wpa_s, MSG_DEBUG, "Interworking: "
					"start ANQP fetch since no matching "
					"networks found");
				wpa_s->network_select = 1;
				wpa_s->auto_network_select = 1;
				interworking_start_fetch_anqp(wpa_s);
				return 1;
			}
#endif /* CONFIG_INTERWORKING */
#ifdef CONFIG_WPS
			if (wpa_s->after_wps > 0 || wpas_wps_searching(wpa_s)) {
				wpa_dbg(wpa_s, MSG_DEBUG, "Use shorter wait during WPS processing");
				timeout_sec = 0;
				timeout_usec = 500000;
				wpa_supplicant_req_new_scan(wpa_s, timeout_sec,
							    timeout_usec);
				return 0;
			}
#endif /* CONFIG_WPS */
#ifdef CONFIG_OWE
			if (wpa_s->owe_transition_search) {
				wpa_dbg(wpa_s, MSG_DEBUG,
					"OWE: Use shorter wait during transition mode search");
				timeout_sec = 0;
				timeout_usec = 500000;
				wpa_supplicant_req_new_scan(wpa_s, timeout_sec,
							    timeout_usec);
				return 0;
			}
#endif /* CONFIG_OWE */
			if (wpa_supplicant_req_sched_scan(wpa_s))
				wpa_supplicant_req_new_scan(wpa_s, timeout_sec,
							    timeout_usec);

			wpa_msg_ctrl(wpa_s, MSG_INFO,
				     WPA_EVENT_NETWORK_NOT_FOUND);
		}
	}
	return 0;
}