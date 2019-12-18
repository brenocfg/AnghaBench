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
struct wpa_supplicant {scalar_t__ wpa_state; int own_disconnect_req; struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ WPA_ASSOCIATED ; 

DBusMessage * wpas_dbus_handler_expect_disconnect(DBusMessage *message,
						  struct wpa_global *global)
{
	struct wpa_supplicant *wpa_s = global->ifaces;

	for (; wpa_s; wpa_s = wpa_s->next)
		if (wpa_s->wpa_state >= WPA_ASSOCIATED)
			wpa_s->own_disconnect_req = 1;
	return NULL;
}