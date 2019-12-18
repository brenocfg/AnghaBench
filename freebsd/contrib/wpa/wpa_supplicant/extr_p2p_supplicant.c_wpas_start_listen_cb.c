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
struct wpas_p2p_listen_work {unsigned int duration; scalar_t__ freq; int /*<<< orphan*/  probe_resp_ie; } ;
struct wpa_supplicant {unsigned int pending_listen_duration; scalar_t__ roc_waiting_drv_freq; scalar_t__ off_channel_freq; scalar_t__ pending_listen_freq; scalar_t__ extra_roc_dur; struct wpa_radio_work* p2p_listen_work; } ;
struct wpa_radio_work {scalar_t__ started; struct wpas_p2p_listen_work* ctx; struct wpa_supplicant* wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ wpa_drv_probe_req_report (struct wpa_supplicant*,int) ; 
 scalar_t__ wpa_drv_remain_on_channel (struct wpa_supplicant*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  wpa_drv_set_ap_wps_ie (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_p2p_listen_work_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_listen_work_free (struct wpas_p2p_listen_work*) ; 
 int /*<<< orphan*/  wpas_stop_listen (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_start_listen_cb(struct wpa_radio_work *work, int deinit)
{
	struct wpa_supplicant *wpa_s = work->wpa_s;
	struct wpas_p2p_listen_work *lwork = work->ctx;
	unsigned int duration;

	if (deinit) {
		if (work->started) {
			wpa_s->p2p_listen_work = NULL;
			wpas_stop_listen(wpa_s);
		}
		wpas_p2p_listen_work_free(lwork);
		return;
	}

	wpa_s->p2p_listen_work = work;

	wpa_drv_set_ap_wps_ie(wpa_s, NULL, lwork->probe_resp_ie, NULL);

	if (wpa_drv_probe_req_report(wpa_s, 1) < 0) {
		wpa_printf(MSG_DEBUG, "P2P: Failed to request the driver to "
			   "report received Probe Request frames");
		wpas_p2p_listen_work_done(wpa_s);
		return;
	}

	wpa_s->pending_listen_freq = lwork->freq;
	wpa_s->pending_listen_duration = lwork->duration;

	duration = lwork->duration;
#ifdef CONFIG_TESTING_OPTIONS
	if (wpa_s->extra_roc_dur) {
		wpa_printf(MSG_DEBUG, "TESTING: Increase ROC duration %u -> %u",
			   duration, duration + wpa_s->extra_roc_dur);
		duration += wpa_s->extra_roc_dur;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (wpa_drv_remain_on_channel(wpa_s, lwork->freq, duration) < 0) {
		wpa_printf(MSG_DEBUG, "P2P: Failed to request the driver "
			   "to remain on channel (%u MHz) for Listen "
			   "state", lwork->freq);
		wpas_p2p_listen_work_done(wpa_s);
		wpa_s->pending_listen_freq = 0;
		return;
	}
	wpa_s->off_channel_freq = 0;
	wpa_s->roc_waiting_drv_freq = lwork->freq;
}