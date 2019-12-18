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
 int /*<<< orphan*/  wpas_dbus_unregister_interface (struct wpa_supplicant*) ; 

void wpas_notify_iface_removed(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->p2p_mgmt)
		return;

	/* unregister interface in new DBus ctrl iface */
	wpas_dbus_unregister_interface(wpa_s);
}