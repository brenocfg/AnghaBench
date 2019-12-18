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
struct wpa_config_blob {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  DBUS_TYPE_BYTE ; 
 int /*<<< orphan*/  DBUS_TYPE_BYTE_AS_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_BLOB_UNKNOWN ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_append_fixed_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 struct wpa_config_blob* wpa_config_get_blob (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_get_blob(DBusMessage *message,
					 struct wpa_supplicant *wpa_s)
{
	DBusMessage *reply = NULL;
	DBusMessageIter	iter, array_iter;

	char *blob_name;
	const struct wpa_config_blob *blob;

	dbus_message_get_args(message, NULL, DBUS_TYPE_STRING, &blob_name,
			      DBUS_TYPE_INVALID);

	blob = wpa_config_get_blob(wpa_s->conf, blob_name);
	if (!blob) {
		return dbus_message_new_error(message,
					      WPAS_DBUS_ERROR_BLOB_UNKNOWN,
					      "Blob id not set");
	}

	reply = dbus_message_new_method_return(message);
	if (!reply)
		return wpas_dbus_error_no_memory(message);

	dbus_message_iter_init_append(reply, &iter);

	if (!dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY,
					      DBUS_TYPE_BYTE_AS_STRING,
					      &array_iter) ||
	    !dbus_message_iter_append_fixed_array(&array_iter, DBUS_TYPE_BYTE,
						  &(blob->data), blob->len) ||
	    !dbus_message_iter_close_container(&iter, &array_iter)) {
		dbus_message_unref(reply);
		reply = wpas_dbus_error_no_memory(message);
	}

	return reply;
}