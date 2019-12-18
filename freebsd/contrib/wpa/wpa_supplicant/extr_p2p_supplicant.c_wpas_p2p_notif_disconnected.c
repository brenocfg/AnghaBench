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
struct wpa_supplicant {int /*<<< orphan*/  ap_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_is_timeout_registered (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_p2p_disable_cross_connect (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_p2p_group_idle_timeout ; 
 int /*<<< orphan*/  wpas_p2p_set_group_idle_timeout (struct wpa_supplicant*) ; 

void wpas_p2p_notif_disconnected(struct wpa_supplicant *wpa_s)
{
	wpas_p2p_disable_cross_connect(wpa_s);
	if (!wpa_s->ap_iface &&
	    !eloop_is_timeout_registered(wpas_p2p_group_idle_timeout,
					 wpa_s, NULL))
		wpas_p2p_set_group_idle_timeout(wpa_s);
}