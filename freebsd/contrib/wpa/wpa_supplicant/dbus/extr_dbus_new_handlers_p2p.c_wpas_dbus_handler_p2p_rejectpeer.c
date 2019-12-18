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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_peer_object_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wpas_p2p_reject (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_p2p_rejectpeer(DBusMessage *message,
					       struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter;
	char *peer_object_path = NULL;
	u8 peer_addr[ETH_ALEN];

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &peer_object_path);

	if (parse_peer_object_path(peer_object_path, peer_addr) < 0)
		return wpas_dbus_error_invalid_args(message, NULL);

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	if (wpas_p2p_reject(wpa_s, peer_addr) < 0)
		return wpas_dbus_error_unknown_error(message,
				"Failed to call wpas_p2p_reject method.");

	return NULL;
}