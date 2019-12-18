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
struct wpa_dbus_object_desc {int /*<<< orphan*/  user_data; struct wpa_dbus_method_desc* methods; } ;
struct wpa_dbus_method_desc {int /*<<< orphan*/ * (* method_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * dbus_method; int /*<<< orphan*/ * dbus_interface; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_ERROR_UNKNOWN_METHOD ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPAS_DBUS_INTERFACE_MAX ; 
 int /*<<< orphan*/  WPAS_DBUS_METHOD_SIGNAL_PROP_MAX ; 
 char* dbus_message_get_interface (int /*<<< orphan*/ *) ; 
 char* dbus_message_get_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_signature_correct (int /*<<< orphan*/ *,struct wpa_dbus_method_desc const*) ; 
 int /*<<< orphan*/  os_strncmp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DBusMessage * msg_method_handler(DBusMessage *message,
					struct wpa_dbus_object_desc *obj_dsc)
{
	const struct wpa_dbus_method_desc *method_dsc = obj_dsc->methods;
	const char *method;
	const char *msg_interface;

	method = dbus_message_get_member(message);
	msg_interface = dbus_message_get_interface(message);

	/* try match call to any registered method */
	while (method_dsc && method_dsc->dbus_method) {
		/* compare method names and interfaces */
		if (!os_strncmp(method_dsc->dbus_method, method,
				WPAS_DBUS_METHOD_SIGNAL_PROP_MAX) &&
		    !os_strncmp(method_dsc->dbus_interface, msg_interface,
				WPAS_DBUS_INTERFACE_MAX))
			break;

		method_dsc++;
	}
	if (method_dsc == NULL || method_dsc->dbus_method == NULL) {
		wpa_printf(MSG_DEBUG, "no method handler for %s.%s on %s",
			   msg_interface, method,
			   dbus_message_get_path(message));
		return dbus_message_new_error(message,
					      DBUS_ERROR_UNKNOWN_METHOD, NULL);
	}

	if (!is_signature_correct(message, method_dsc)) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      NULL);
	}

	return method_dsc->method_handler(message, obj_dsc->user_data);
}