#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {scalar_t__ p2p_group_common_freqs_num; TYPE_3__* p2p_group_common_freqs; int /*<<< orphan*/ * p2p_oob_dev_pw; TYPE_2__* p2p_send_action_work; scalar_t__ p2p_long_listen; TYPE_3__* go_params; TYPE_1__* global; scalar_t__ drv_priv; scalar_t__ driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  peer_device_addr; } ;
struct TYPE_5__ {TYPE_3__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (TYPE_3__*) ; 
 int /*<<< orphan*/  p2p_clear_provisioning_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_work_done (TYPE_2__*) ; 
 int /*<<< orphan*/  wpa_drv_probe_req_report (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_timeout ; 
 int /*<<< orphan*/  wpas_p2p_group_freq_conflict ; 
 int /*<<< orphan*/  wpas_p2p_group_idle_timeout ; 
 int /*<<< orphan*/  wpas_p2p_join_scan ; 
 int /*<<< orphan*/  wpas_p2p_listen_work_done (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_long_listen_timeout ; 
 int /*<<< orphan*/  wpas_p2p_psk_failure_removal ; 
 int /*<<< orphan*/  wpas_p2p_remove_pending_group_interface (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_send_action_work_timeout ; 

void wpas_p2p_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver && wpa_s->drv_priv)
		wpa_drv_probe_req_report(wpa_s, 0);

	if (wpa_s->go_params) {
		/* Clear any stored provisioning info */
		p2p_clear_provisioning_info(
			wpa_s->global->p2p,
			wpa_s->go_params->peer_device_addr);
	}

	os_free(wpa_s->go_params);
	wpa_s->go_params = NULL;
	eloop_cancel_timeout(wpas_p2p_psk_failure_removal, wpa_s, NULL);
	eloop_cancel_timeout(wpas_p2p_group_formation_timeout, wpa_s, NULL);
	eloop_cancel_timeout(wpas_p2p_join_scan, wpa_s, NULL);
	wpa_s->p2p_long_listen = 0;
	eloop_cancel_timeout(wpas_p2p_long_listen_timeout, wpa_s, NULL);
	eloop_cancel_timeout(wpas_p2p_group_idle_timeout, wpa_s, NULL);
	wpas_p2p_remove_pending_group_interface(wpa_s);
	eloop_cancel_timeout(wpas_p2p_group_freq_conflict, wpa_s, NULL);
	wpas_p2p_listen_work_done(wpa_s);
	if (wpa_s->p2p_send_action_work) {
		os_free(wpa_s->p2p_send_action_work->ctx);
		radio_work_done(wpa_s->p2p_send_action_work);
		wpa_s->p2p_send_action_work = NULL;
	}
	eloop_cancel_timeout(wpas_p2p_send_action_work_timeout, wpa_s, NULL);

	wpabuf_free(wpa_s->p2p_oob_dev_pw);
	wpa_s->p2p_oob_dev_pw = NULL;

	os_free(wpa_s->p2p_group_common_freqs);
	wpa_s->p2p_group_common_freqs = NULL;
	wpa_s->p2p_group_common_freqs_num = 0;

	/* TODO: remove group interface from the driver if this wpa_s instance
	 * is on top of a P2P group interface */
}