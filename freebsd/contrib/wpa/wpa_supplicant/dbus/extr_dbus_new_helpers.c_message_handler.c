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
struct wpa_dbus_object_desc {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusHandlerResult ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_UNKNOWN_METHOD ; 
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_HANDLED ; 
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_NOT_YET_HANDLED ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  WPAS_DBUS_INTERFACE_MAX ; 
 int /*<<< orphan*/  WPAS_DBUS_METHOD_SIGNAL_PROP_MAX ; 
 int /*<<< orphan*/  WPA_DBUS_INTROSPECTION_INTERFACE ; 
 int /*<<< orphan*/  WPA_DBUS_INTROSPECTION_METHOD ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_INTERFACE ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* dbus_message_get_interface (int /*<<< orphan*/ *) ; 
 char* dbus_message_get_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_no_reply (int /*<<< orphan*/ *) ; 
 char* dbus_message_get_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_signature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msg_method_handler (int /*<<< orphan*/ *,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  os_strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * properties_handler (int /*<<< orphan*/ *,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  wpa_dbus_flush_all_changed_properties (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpa_dbus_introspect (int /*<<< orphan*/ *,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DBusHandlerResult message_handler(DBusConnection *connection,
					 DBusMessage *message, void *user_data)
{
	struct wpa_dbus_object_desc *obj_dsc = user_data;
	const char *method;
	const char *path;
	const char *msg_interface;
	DBusMessage *reply;

	/* get method, interface and path the message is addressed to */
	method = dbus_message_get_member(message);
	path = dbus_message_get_path(message);
	msg_interface = dbus_message_get_interface(message);
	if (!method || !path || !msg_interface)
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	wpa_printf(MSG_MSGDUMP, "dbus: %s.%s (%s) [%s]",
		   msg_interface, method, path,
		   dbus_message_get_signature(message));

	/* if message is introspection method call */
	if (!os_strncmp(WPA_DBUS_INTROSPECTION_METHOD, method,
			WPAS_DBUS_METHOD_SIGNAL_PROP_MAX) &&
	    !os_strncmp(WPA_DBUS_INTROSPECTION_INTERFACE, msg_interface,
			WPAS_DBUS_INTERFACE_MAX)) {
#ifdef CONFIG_CTRL_IFACE_DBUS_INTRO
		reply = wpa_dbus_introspect(message, obj_dsc);
#else /* CONFIG_CTRL_IFACE_DBUS_INTRO */
		reply = dbus_message_new_error(
			message, DBUS_ERROR_UNKNOWN_METHOD,
			"wpa_supplicant was compiled without introspection support.");
#endif /* CONFIG_CTRL_IFACE_DBUS_INTRO */
	} else if (!os_strncmp(WPA_DBUS_PROPERTIES_INTERFACE, msg_interface,
			     WPAS_DBUS_INTERFACE_MAX)) {
		/* if message is properties method call */
		reply = properties_handler(message, obj_dsc);
	} else {
		reply = msg_method_handler(message, obj_dsc);
	}

	/* If handler succeed returning NULL, reply empty message */
	if (!reply)
		reply = dbus_message_new_method_return(message);
	if (reply) {
		if (!dbus_message_get_no_reply(message))
			dbus_connection_send(connection, reply, NULL);
		dbus_message_unref(reply);
	}

	wpa_dbus_flush_all_changed_properties(connection);

	return DBUS_HANDLER_RESULT_HANDLED;
}