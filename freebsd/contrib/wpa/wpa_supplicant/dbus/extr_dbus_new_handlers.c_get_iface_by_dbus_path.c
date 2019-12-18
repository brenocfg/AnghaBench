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
struct wpa_supplicant {scalar_t__ dbus_new_path; struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct wpa_supplicant * get_iface_by_dbus_path(
	struct wpa_global *global, const char *path)
{
	struct wpa_supplicant *wpa_s;

	for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		if (wpa_s->dbus_new_path &&
		    os_strcmp(wpa_s->dbus_new_path, path) == 0)
			return wpa_s;
	}
	return NULL;
}