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
struct wpa_supplicant {scalar_t__ show_group_started; scalar_t__ p2p_in_provisioning; TYPE_2__* current_ssid; TYPE_1__* conf; } ;
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  p2p_group; } ;
struct TYPE_3__ {int p2p_group_idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int P2P_MAX_CLIENT_IDLE ; 
 scalar_t__ WPAS_MODE_INFRA ; 
 scalar_t__ eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_p2p_group_idle_timeout ; 

__attribute__((used)) static void wpas_p2p_set_group_idle_timeout(struct wpa_supplicant *wpa_s)
{
	int timeout;

	if (eloop_cancel_timeout(wpas_p2p_group_idle_timeout, wpa_s, NULL) > 0)
		wpa_printf(MSG_DEBUG, "P2P: Cancelled P2P group idle timeout");

	if (wpa_s->current_ssid == NULL || !wpa_s->current_ssid->p2p_group)
		return;

	timeout = wpa_s->conf->p2p_group_idle;
	if (wpa_s->current_ssid->mode == WPAS_MODE_INFRA &&
	    (timeout == 0 || timeout > P2P_MAX_CLIENT_IDLE))
	    timeout = P2P_MAX_CLIENT_IDLE;

	if (timeout == 0)
		return;

	if (timeout < 0) {
		if (wpa_s->current_ssid->mode == WPAS_MODE_INFRA)
			timeout = 0; /* special client mode no-timeout */
		else
			return;
	}

	if (wpa_s->p2p_in_provisioning) {
		/*
		 * Use the normal group formation timeout during the
		 * provisioning phase to avoid terminating this process too
		 * early due to group idle timeout.
		 */
		wpa_printf(MSG_DEBUG, "P2P: Do not use P2P group idle timeout "
			   "during provisioning");
		return;
	}

	if (wpa_s->show_group_started) {
		/*
		 * Use the normal group formation timeout between the end of
		 * the provisioning phase and completion of 4-way handshake to
		 * avoid terminating this process too early due to group idle
		 * timeout.
		 */
		wpa_printf(MSG_DEBUG, "P2P: Do not use P2P group idle timeout "
			   "while waiting for initial 4-way handshake to "
			   "complete");
		return;
	}

	wpa_printf(MSG_DEBUG, "P2P: Set P2P group idle timeout to %u seconds",
		   timeout);
	eloop_register_timeout(timeout, 0, wpas_p2p_group_idle_timeout,
			       wpa_s, NULL);
}