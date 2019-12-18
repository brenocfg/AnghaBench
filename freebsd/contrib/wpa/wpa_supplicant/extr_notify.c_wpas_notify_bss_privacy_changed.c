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
 int /*<<< orphan*/  WPAS_DBUS_BSS_PROP_PRIVACY ; 
 int /*<<< orphan*/  wpas_dbus_bss_signal_prop_changed (struct wpa_supplicant*,int /*<<< orphan*/ ,unsigned int) ; 

void wpas_notify_bss_privacy_changed(struct wpa_supplicant *wpa_s,
				     unsigned int id)
{
	if (wpa_s->p2p_mgmt)
		return;

	wpas_dbus_bss_signal_prop_changed(wpa_s, WPAS_DBUS_BSS_PROP_PRIVACY,
					  id);
}