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
struct wpa_supplicant {int /*<<< orphan*/  wpa; struct wpa_radio_work* connect_work; } ;
struct wpa_radio_work {scalar_t__ started; struct wpa_supplicant* wpa_s; struct wpa_connect_work* ctx; } ;
struct wpa_connect_work {int /*<<< orphan*/  ssid; int /*<<< orphan*/  bss; scalar_t__ bss_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  sme_send_authentication (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_set_assoc_wpa_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_connect_work_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_connect_work_free (struct wpa_connect_work*) ; 
 scalar_t__ wpas_network_disabled (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_valid_bss_ssid (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sme_auth_start_cb(struct wpa_radio_work *work, int deinit)
{
	struct wpa_connect_work *cwork = work->ctx;
	struct wpa_supplicant *wpa_s = work->wpa_s;

	if (deinit) {
		if (work->started)
			wpa_s->connect_work = NULL;

		wpas_connect_work_free(cwork);
		return;
	}

	wpa_s->connect_work = work;

	if (cwork->bss_removed ||
	    !wpas_valid_bss_ssid(wpa_s, cwork->bss, cwork->ssid) ||
	    wpas_network_disabled(wpa_s, cwork->ssid)) {
		wpa_dbg(wpa_s, MSG_DEBUG, "SME: BSS/SSID entry for authentication not valid anymore - drop connection attempt");
		wpas_connect_work_done(wpa_s);
		return;
	}

	/* Starting new connection, so clear the possibly used WPA IE from the
	 * previous association. */
	wpa_sm_set_assoc_wpa_ie(wpa_s->wpa, NULL, 0);

	sme_send_authentication(wpa_s, cwork->bss, cwork->ssid, 1);
}