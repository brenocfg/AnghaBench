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
struct wpa_supplicant {scalar_t__ p2p_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_signal_wps_event_success (struct wpa_supplicant*) ; 

void wpas_notify_wps_event_success(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->p2p_mgmt)
		return;

#ifdef CONFIG_WPS
	wpas_dbus_signal_wps_event_success(wpa_s);
#endif /* CONFIG_WPS */
}