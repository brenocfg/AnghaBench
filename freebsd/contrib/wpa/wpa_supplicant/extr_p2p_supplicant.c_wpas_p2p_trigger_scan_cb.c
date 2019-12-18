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
struct wpa_supplicant {int own_scan_requested; struct wpa_radio_work* p2p_scan_work; scalar_t__ clear_driver_scan_cache; int /*<<< orphan*/  scan_res_handler; int /*<<< orphan*/  scan_trigger_time; TYPE_1__* global; int /*<<< orphan*/  curr_scan_cookie; } ;
struct wpa_radio_work {struct wpa_driver_scan_params* ctx; int /*<<< orphan*/  started; struct wpa_supplicant* wpa_s; } ;
struct wpa_driver_scan_params {int only_new_results; int /*<<< orphan*/  scan_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_notify_scan_trigger_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radio_work_done (struct wpa_radio_work*) ; 
 int wpa_drv_scan (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_scan_free_params (struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  wpas_p2p_scan_res_handler ; 

__attribute__((used)) static void wpas_p2p_trigger_scan_cb(struct wpa_radio_work *work, int deinit)
{
	struct wpa_supplicant *wpa_s = work->wpa_s;
	struct wpa_driver_scan_params *params = work->ctx;
	int ret;

	if (deinit) {
		if (!work->started) {
			wpa_scan_free_params(params);
			return;
		}

		wpa_s->p2p_scan_work = NULL;
		return;
	}

	if (wpa_s->clear_driver_scan_cache) {
		wpa_printf(MSG_DEBUG,
			   "Request driver to clear scan cache due to local BSS flush");
		params->only_new_results = 1;
	}
	ret = wpa_drv_scan(wpa_s, params);
	if (ret == 0)
		wpa_s->curr_scan_cookie = params->scan_cookie;
	wpa_scan_free_params(params);
	work->ctx = NULL;
	if (ret) {
		radio_work_done(work);
		p2p_notify_scan_trigger_status(wpa_s->global->p2p, ret);
		return;
	}

	p2p_notify_scan_trigger_status(wpa_s->global->p2p, ret);
	os_get_reltime(&wpa_s->scan_trigger_time);
	wpa_s->scan_res_handler = wpas_p2p_scan_res_handler;
	wpa_s->own_scan_requested = 1;
	wpa_s->clear_driver_scan_cache = 0;
	wpa_s->p2p_scan_work = work;
}