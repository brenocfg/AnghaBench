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
struct wpa_dbus_object_desc {int /*<<< orphan*/  user_data; int /*<<< orphan*/  properties; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  dbus_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_dict_with_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_reply_new_from_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static DBusMessage * get_all_properties(DBusMessage *message, char *interface,
					struct wpa_dbus_object_desc *obj_dsc)
{
	DBusMessage *reply;
	DBusMessageIter iter, dict_iter;
	DBusError error;

	reply = dbus_message_new_method_return(message);
	if (reply == NULL)
		return wpas_dbus_error_no_memory(message);

	dbus_message_iter_init_append(reply, &iter);
	if (!wpa_dbus_dict_open_write(&iter, &dict_iter)) {
		dbus_message_unref(reply);
		return wpas_dbus_error_no_memory(message);
	}

	dbus_error_init(&error);
	if (!fill_dict_with_properties(&dict_iter, obj_dsc->properties,
				       interface, obj_dsc->user_data, &error)) {
		wpa_dbus_dict_close_write(&iter, &dict_iter);
		dbus_message_unref(reply);
		reply = wpas_dbus_reply_new_from_error(
			message, &error, DBUS_ERROR_INVALID_ARGS,
			"No readable properties in this interface");
		dbus_error_free(&error);
		return reply;
	}

	if (!wpa_dbus_dict_close_write(&iter, &dict_iter)) {
		dbus_message_unref(reply);
		return wpas_dbus_error_no_memory(message);
	}

	return reply;
}