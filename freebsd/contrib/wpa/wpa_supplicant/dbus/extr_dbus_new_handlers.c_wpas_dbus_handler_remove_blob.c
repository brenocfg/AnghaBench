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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_BLOB_UNKNOWN ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_config_remove_blob (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_notify_blob_removed (struct wpa_supplicant*,char*) ; 

DBusMessage * wpas_dbus_handler_remove_blob(DBusMessage *message,
					    struct wpa_supplicant *wpa_s)
{
	DBusMessage *reply = NULL;
	char *blob_name;

	dbus_message_get_args(message, NULL, DBUS_TYPE_STRING, &blob_name,
			      DBUS_TYPE_INVALID);

	if (wpa_config_remove_blob(wpa_s->conf, blob_name)) {
		return dbus_message_new_error(message,
					      WPAS_DBUS_ERROR_BLOB_UNKNOWN,
					      "Blob id not set");
	}
	wpas_notify_blob_removed(wpa_s, blob_name);

	return reply;

}