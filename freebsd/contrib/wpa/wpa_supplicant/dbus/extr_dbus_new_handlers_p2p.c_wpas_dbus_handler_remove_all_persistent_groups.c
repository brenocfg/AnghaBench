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
struct wpa_supplicant {struct wpa_config* conf; TYPE_1__* global; } ;
struct wpa_ssid {struct wpa_ssid* next; } ;
struct wpa_config {struct wpa_ssid* ssid; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ network_is_persistent_group (struct wpa_ssid*) ; 
 int /*<<< orphan*/  remove_persistent_group (struct wpa_supplicant*,struct wpa_ssid*) ; 

DBusMessage * wpas_dbus_handler_remove_all_persistent_groups(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	struct wpa_ssid *ssid, *next;
	struct wpa_config *config;

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	config = wpa_s->conf;
	ssid = config->ssid;
	while (ssid) {
		next = ssid->next;
		if (network_is_persistent_group(ssid))
			remove_persistent_group(wpa_s, ssid);
		ssid = next;
	}
	return NULL;
}