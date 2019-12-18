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
struct wpa_supplicant {int dummy; } ;
struct wpa_ssid {int disabled; int p2p_persistent_group; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_register_network (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_dbus_register_persistent_group (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_dbus_unregister_network (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_dbus_unregister_persistent_group (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

void wpas_notify_network_type_changed(struct wpa_supplicant *wpa_s,
				      struct wpa_ssid *ssid)
{
#ifdef CONFIG_P2P
	if (ssid->disabled == 2) {
		/* Changed from normal network profile to persistent group */
		ssid->disabled = 0;
		wpas_dbus_unregister_network(wpa_s, ssid->id);
		ssid->disabled = 2;
		ssid->p2p_persistent_group = 1;
		wpas_dbus_register_persistent_group(wpa_s, ssid);
	} else {
		/* Changed from persistent group to normal network profile */
		wpas_dbus_unregister_persistent_group(wpa_s, ssid->id);
		ssid->p2p_persistent_group = 0;
		wpas_dbus_register_network(wpa_s, ssid);
	}
#endif /* CONFIG_P2P */
}