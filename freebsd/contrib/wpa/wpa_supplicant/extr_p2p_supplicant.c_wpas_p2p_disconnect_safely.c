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
struct wpa_supplicant {scalar_t__ p2p_group_interface; } ;

/* Variables and functions */
 scalar_t__ NOT_P2P_GROUP_INTERFACE ; 
 scalar_t__ eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_wpas_p2p_disconnect ; 
 int wpas_p2p_disconnect (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpas_p2p_disconnect_safely(struct wpa_supplicant *wpa_s,
				      struct wpa_supplicant *calling_wpa_s)
{
	if (calling_wpa_s == wpa_s && wpa_s &&
	    wpa_s->p2p_group_interface != NOT_P2P_GROUP_INTERFACE) {
		/*
		 * The calling wpa_s instance is going to be removed. Do that
		 * from an eloop callback to keep the instance available until
		 * the caller has returned. This my be needed, e.g., to provide
		 * control interface responses on the per-interface socket.
		 */
		if (eloop_register_timeout(0, 0, run_wpas_p2p_disconnect,
					   wpa_s, NULL) < 0)
			return -1;
		return 0;
	}

	return wpas_p2p_disconnect(wpa_s);
}