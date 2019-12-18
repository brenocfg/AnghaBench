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
struct wpa_supplicant {unsigned int p2p_long_listen; unsigned int max_remain_on_chan; TYPE_1__* global; scalar_t__ p2p_lo_started; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_stop_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_clear_pending_action_tx (struct wpa_supplicant*) ; 
 int wpas_p2p_listen_start (struct wpa_supplicant*,unsigned int) ; 
 int /*<<< orphan*/  wpas_p2p_long_listen_timeout ; 

int wpas_p2p_listen(struct wpa_supplicant *wpa_s, unsigned int timeout)
{
	int res;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return -1;

	if (wpa_s->p2p_lo_started) {
		wpa_printf(MSG_DEBUG,
			"P2P: Cannot start P2P listen, it is offloaded");
		return -1;
	}

	wpa_supplicant_cancel_sched_scan(wpa_s);
	wpas_p2p_clear_pending_action_tx(wpa_s);

	if (timeout == 0) {
		/*
		 * This is a request for unlimited Listen state. However, at
		 * least for now, this is mapped to a Listen state for one
		 * hour.
		 */
		timeout = 3600;
	}
	eloop_cancel_timeout(wpas_p2p_long_listen_timeout, wpa_s, NULL);
	wpa_s->p2p_long_listen = 0;

	/*
	 * Stop previous find/listen operation to avoid trying to request a new
	 * remain-on-channel operation while the driver is still running the
	 * previous one.
	 */
	if (wpa_s->global->p2p)
		p2p_stop_find(wpa_s->global->p2p);

	res = wpas_p2p_listen_start(wpa_s, timeout * 1000);
	if (res == 0 && timeout * 1000 > wpa_s->max_remain_on_chan) {
		wpa_s->p2p_long_listen = timeout * 1000;
		eloop_register_timeout(timeout, 0,
				       wpas_p2p_long_listen_timeout,
				       wpa_s, NULL);
	}

	return res;
}