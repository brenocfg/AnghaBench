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
struct wpa_supplicant {scalar_t__ p2p_group_interface; TYPE_1__* current_ssid; struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;
struct TYPE_2__ {scalar_t__ p2p_group; } ;

/* Variables and functions */
 scalar_t__ NOT_P2P_GROUP_INTERFACE ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  wpas_p2p_disconnect (struct wpa_supplicant*) ; 
 int wpas_wps_terminate_pending (struct wpa_supplicant*) ; 

void wpa_supplicant_terminate_proc(struct wpa_global *global)
{
	int pending = 0;
#ifdef CONFIG_WPS
	struct wpa_supplicant *wpa_s = global->ifaces;
	while (wpa_s) {
		struct wpa_supplicant *next = wpa_s->next;
		if (wpas_wps_terminate_pending(wpa_s) == 1)
			pending = 1;
#ifdef CONFIG_P2P
		if (wpa_s->p2p_group_interface != NOT_P2P_GROUP_INTERFACE ||
		    (wpa_s->current_ssid && wpa_s->current_ssid->p2p_group))
			wpas_p2p_disconnect(wpa_s);
#endif /* CONFIG_P2P */
		wpa_s = next;
	}
#endif /* CONFIG_WPS */
	if (pending)
		return;
	eloop_terminate();
}