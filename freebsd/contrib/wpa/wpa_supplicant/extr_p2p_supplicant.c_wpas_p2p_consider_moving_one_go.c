#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_used_freq_data {int freq; unsigned int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {int drv_flags; TYPE_5__* global; TYPE_6__* ap_iface; int /*<<< orphan*/  p2p_group; TYPE_3__* conf; TYPE_2__ hw; TYPE_1__* current_ssid; } ;
struct TYPE_12__ {TYPE_4__* current_mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  p2p; } ;
struct TYPE_10__ {scalar_t__ mode; } ;
struct TYPE_9__ {scalar_t__ p2p_go_freq_change_policy; } ;
struct TYPE_7__ {int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned int P2P_GO_FREQ_CHANGE_TIME ; 
 scalar_t__ P2P_GO_FREQ_MOVE_SCM ; 
 scalar_t__ P2P_GO_FREQ_MOVE_SCM_ECSA ; 
 scalar_t__ P2P_GO_FREQ_MOVE_SCM_PEER_SUPPORTS ; 
 unsigned int P2P_RECONSIDER_GO_MOVE_DELAY ; 
 int WPA_DRIVER_FLAGS_AP_CSA ; 
 int WPA_DRIVER_FLAGS_DFS_OFFLOAD ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 scalar_t__ hostapd_csa_in_progress (TYPE_6__*) ; 
 scalar_t__ ieee80211_freq_to_chan (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_is_dfs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_get_group_num_members (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_supported_freq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_supported_freq_go (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_p2p_disallowed_freq (TYPE_5__*,int) ; 
 scalar_t__ wpas_p2p_go_clients_support_ecsa (struct wpa_supplicant*) ; 
 scalar_t__ wpas_p2p_go_is_peer_freq (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpas_p2p_go_update_common_freqs (struct wpa_supplicant*) ; 
 scalar_t__ wpas_p2p_in_progress (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_move_go ; 
 int /*<<< orphan*/  wpas_p2p_reconsider_moving_go ; 

__attribute__((used)) static void wpas_p2p_consider_moving_one_go(struct wpa_supplicant *wpa_s,
					    struct wpa_used_freq_data *freqs,
					    unsigned int num)
{
	unsigned int i, invalid_freq = 0, policy_move = 0, flags = 0;
	unsigned int timeout;
	int freq;
	int dfs_offload;

	wpas_p2p_go_update_common_freqs(wpa_s);

	freq = wpa_s->current_ssid->frequency;
	dfs_offload = (wpa_s->drv_flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD) &&
		ieee80211_is_dfs(freq, wpa_s->hw.modes, wpa_s->hw.num_modes);
	for (i = 0, invalid_freq = 0; i < num; i++) {
		if (freqs[i].freq == freq) {
			flags = freqs[i].flags;

			/* The channel is invalid, must change it */
			if (!p2p_supported_freq_go(wpa_s->global->p2p, freq) &&
			    !dfs_offload) {
				wpa_dbg(wpa_s, MSG_DEBUG,
					"P2P: Freq=%d MHz no longer valid for GO",
					freq);
				invalid_freq = 1;
			}
		} else if (freqs[i].flags == 0) {
			/* Freq is not used by any other station interface */
			continue;
		} else if (!p2p_supported_freq(wpa_s->global->p2p,
					       freqs[i].freq) && !dfs_offload) {
			/* Freq is not valid for P2P use cases */
			continue;
		} else if (wpa_s->conf->p2p_go_freq_change_policy ==
			   P2P_GO_FREQ_MOVE_SCM) {
			policy_move = 1;
		} else if (wpa_s->conf->p2p_go_freq_change_policy ==
			   P2P_GO_FREQ_MOVE_SCM_PEER_SUPPORTS &&
			   wpas_p2p_go_is_peer_freq(wpa_s, freqs[i].freq)) {
			policy_move = 1;
		} else if ((wpa_s->conf->p2p_go_freq_change_policy ==
			    P2P_GO_FREQ_MOVE_SCM_ECSA) &&
			   wpas_p2p_go_is_peer_freq(wpa_s, freqs[i].freq)) {
			if (!p2p_get_group_num_members(wpa_s->p2p_group)) {
				policy_move = 1;
			} else if ((wpa_s->drv_flags &
				    WPA_DRIVER_FLAGS_AP_CSA) &&
				   wpas_p2p_go_clients_support_ecsa(wpa_s)) {
				u8 chan;

				/*
				 * We do not support CSA between bands, so move
				 * GO only within the same band.
				 */
				if (wpa_s->ap_iface->current_mode->mode ==
				    ieee80211_freq_to_chan(freqs[i].freq,
							   &chan))
					policy_move = 1;
			}
		}
	}

	wpa_dbg(wpa_s, MSG_DEBUG,
		"P2P: GO move: invalid_freq=%u, policy_move=%u, flags=0x%X",
		invalid_freq, policy_move, flags);

	/*
	 * The channel is valid, or we are going to have a policy move, so
	 * cancel timeout.
	 */
	if (!invalid_freq || policy_move) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Cancel a GO move from freq=%d MHz", freq);
		eloop_cancel_timeout(wpas_p2p_move_go, wpa_s, NULL);

		if (wpas_p2p_in_progress(wpa_s)) {
			wpa_dbg(wpa_s, MSG_DEBUG,
				"P2P: GO move: policy CS is not allowed - setting timeout to re-consider GO move");
			eloop_cancel_timeout(wpas_p2p_reconsider_moving_go,
					     wpa_s, NULL);
			eloop_register_timeout(P2P_RECONSIDER_GO_MOVE_DELAY, 0,
					       wpas_p2p_reconsider_moving_go,
					       wpa_s, NULL);
			return;
		}
	}

	if (!invalid_freq && (!policy_move || flags != 0)) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Not initiating a GO frequency change");
		return;
	}

	/*
	 * Do not consider moving GO if it is in the middle of a CSA. When the
	 * CSA is finished this flow should be retriggered.
	 */
	if (hostapd_csa_in_progress(wpa_s->ap_iface)) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Not initiating a GO frequency change - CSA is in progress");
		return;
	}

	if (invalid_freq && !wpas_p2p_disallowed_freq(wpa_s->global, freq))
		timeout = P2P_GO_FREQ_CHANGE_TIME;
	else
		timeout = 0;

	wpa_dbg(wpa_s, MSG_DEBUG, "P2P: Move GO from freq=%d MHz in %d secs",
		freq, timeout);
	eloop_cancel_timeout(wpas_p2p_move_go, wpa_s, NULL);
	eloop_register_timeout(timeout, 0, wpas_p2p_move_go, wpa_s, NULL);
}