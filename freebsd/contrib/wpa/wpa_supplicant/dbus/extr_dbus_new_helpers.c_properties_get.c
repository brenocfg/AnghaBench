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
struct wpa_dbus_property_desc {scalar_t__ (* getter ) (struct wpa_dbus_property_desc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;} ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_FAILED ; 
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  dbus_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_signature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (struct wpa_dbus_property_desc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * wpas_dbus_reply_new_from_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static DBusMessage * properties_get(DBusMessage *message,
				    const struct wpa_dbus_property_desc *dsc,
				    void *user_data)
{
	DBusMessage *reply;
	DBusMessageIter iter;
	DBusError error;

	if (os_strcmp(dbus_message_get_signature(message), "ss")) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      NULL);
	}

	if (dsc->getter == NULL) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "Property is write-only");
	}

	reply = dbus_message_new_method_return(message);
	dbus_message_iter_init_append(reply, &iter);

	dbus_error_init(&error);
	if (dsc->getter(dsc, &iter, &error, user_data) == FALSE) {
		dbus_message_unref(reply);
		reply = wpas_dbus_reply_new_from_error(
			message, &error, DBUS_ERROR_FAILED,
			"Failed to read property");
		dbus_error_free(&error);
	}

	return reply;
}