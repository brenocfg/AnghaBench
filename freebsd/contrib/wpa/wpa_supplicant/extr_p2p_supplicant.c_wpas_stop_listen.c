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
struct wpa_supplicant {int /*<<< orphan*/  p2p_cli_probe; scalar_t__ roc_waiting_drv_freq; scalar_t__ off_channel_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_drv_cancel_remain_on_channel (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_drv_probe_req_report (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_drv_set_ap_wps_ie (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_p2p_listen_work_done (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_stop_listen(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;
	if (wpa_s->off_channel_freq || wpa_s->roc_waiting_drv_freq) {
		wpa_drv_cancel_remain_on_channel(wpa_s);
		wpa_s->off_channel_freq = 0;
		wpa_s->roc_waiting_drv_freq = 0;
	}
	wpa_drv_set_ap_wps_ie(wpa_s, NULL, NULL, NULL);

	/*
	 * Don't cancel Probe Request RX reporting for a connected P2P Client
	 * handling Probe Request frames.
	 */
	if (!wpa_s->p2p_cli_probe)
		wpa_drv_probe_req_report(wpa_s, 0);

	wpas_p2p_listen_work_done(wpa_s);
}