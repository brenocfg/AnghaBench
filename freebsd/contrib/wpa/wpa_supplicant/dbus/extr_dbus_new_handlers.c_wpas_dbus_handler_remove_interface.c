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
struct wpa_global {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 struct wpa_supplicant* get_iface_by_dbus_path (struct wpa_global*,char*) ; 
 scalar_t__ wpa_supplicant_remove_iface (struct wpa_global*,struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpas_dbus_error_iface_unknown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 

DBusMessage * wpas_dbus_handler_remove_interface(DBusMessage *message,
						 struct wpa_global *global)
{
	struct wpa_supplicant *wpa_s;
	char *path;
	DBusMessage *reply = NULL;

	dbus_message_get_args(message, NULL, DBUS_TYPE_OBJECT_PATH, &path,
			      DBUS_TYPE_INVALID);

	wpa_s = get_iface_by_dbus_path(global, path);
	if (wpa_s == NULL)
		reply = wpas_dbus_error_iface_unknown(message);
	else if (wpa_supplicant_remove_iface(global, wpa_s, 0)) {
		reply = wpas_dbus_error_unknown_error(
			message,
			"wpa_supplicant couldn't remove this interface.");
	}

	return reply;
}