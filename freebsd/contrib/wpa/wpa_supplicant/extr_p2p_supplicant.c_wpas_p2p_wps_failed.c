#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wps_event_fail {int dummy; } ;
struct wpa_supplicant {int /*<<< orphan*/  p2pdev; TYPE_1__* global; TYPE_2__* go_params; int /*<<< orphan*/  p2p_in_provisioning; } ;
struct TYPE_4__ {int /*<<< orphan*/  peer_device_addr; } ;
struct TYPE_3__ {int p2p_fail_on_wps_complete; struct wpa_supplicant* p2p_group_formation; int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_deplete_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_clear_provisioning_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_notify_p2p_wps_failed (struct wpa_supplicant*,struct wps_event_fail*) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_timeout ; 

void wpas_p2p_wps_failed(struct wpa_supplicant *wpa_s,
			 struct wps_event_fail *fail)
{
	if (!wpa_s->p2p_in_provisioning) {
		wpa_printf(MSG_DEBUG, "P2P: Ignore WPS fail event - P2P "
			   "provisioning not in progress");
		return;
	}

	if (wpa_s->go_params) {
		p2p_clear_provisioning_info(
			wpa_s->global->p2p,
			wpa_s->go_params->peer_device_addr);
	}

	wpas_notify_p2p_wps_failed(wpa_s, fail);

	if (wpa_s == wpa_s->global->p2p_group_formation) {
		/*
		 * Allow some time for the failed WPS negotiation exchange to
		 * complete, but remove the group since group formation cannot
		 * succeed after provisioning failure.
		 */
		wpa_printf(MSG_DEBUG, "P2P: WPS step failed during group formation - reject connection from timeout");
		wpa_s->global->p2p_fail_on_wps_complete = 1;
		eloop_deplete_timeout(0, 50000,
				      wpas_p2p_group_formation_timeout,
				      wpa_s->p2pdev, NULL);
	}
}