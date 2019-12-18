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
struct wpa_supplicant {char* dbus_new_path; } ;
struct wpa_global {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 struct wpa_supplicant* wpa_supplicant_get_iface (struct wpa_global*,char const*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_iface_unknown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_get_interface(DBusMessage *message,
					      struct wpa_global *global)
{
	DBusMessage *reply = NULL;
	const char *ifname;
	const char *path;
	struct wpa_supplicant *wpa_s;

	dbus_message_get_args(message, NULL, DBUS_TYPE_STRING, &ifname,
			      DBUS_TYPE_INVALID);

	wpa_s = wpa_supplicant_get_iface(global, ifname);
	if (wpa_s == NULL || wpa_s->dbus_new_path == NULL)
		return wpas_dbus_error_iface_unknown(message);

	path = wpa_s->dbus_new_path;
	reply = dbus_message_new_method_return(message);
	if (reply == NULL)
		return wpas_dbus_error_no_memory(message);
	if (!dbus_message_append_args(reply, DBUS_TYPE_OBJECT_PATH, &path,
				      DBUS_TYPE_INVALID)) {
		dbus_message_unref(reply);
		return wpas_dbus_error_no_memory(message);
	}

	return reply;
}