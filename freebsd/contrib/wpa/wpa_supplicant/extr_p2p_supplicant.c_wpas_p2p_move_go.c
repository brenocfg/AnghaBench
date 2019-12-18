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
struct wpa_supplicant {int /*<<< orphan*/  ap_iface; int /*<<< orphan*/  current_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ hostapd_csa_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_go_update_common_freqs (struct wpa_supplicant*) ; 
 scalar_t__ wpas_p2p_move_go_csa (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_move_go_no_csa (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_p2p_move_go(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;

	if (!wpa_s->ap_iface || !wpa_s->current_ssid)
		return;

	wpas_p2p_go_update_common_freqs(wpa_s);

	/* Do not move GO in the middle of a CSA */
	if (hostapd_csa_in_progress(wpa_s->ap_iface)) {
		wpa_printf(MSG_DEBUG,
			   "P2P: CSA is in progress - not moving GO");
		return;
	}

	/*
	 * First, try a channel switch flow. If it is not supported or fails,
	 * take down the GO and bring it up again.
	 */
	if (wpas_p2p_move_go_csa(wpa_s) < 0)
		wpas_p2p_move_go_no_csa(wpa_s);
}