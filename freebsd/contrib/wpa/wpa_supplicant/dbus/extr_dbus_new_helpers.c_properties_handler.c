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
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_ERROR_UNKNOWN_METHOD ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  WPAS_DBUS_METHOD_SIGNAL_PROP_MAX ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_GET ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_GETALL ; 
 int /*<<< orphan*/  WPA_DBUS_PROPERTIES_SET ; 
 char* dbus_message_get_member (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * properties_get_all (int /*<<< orphan*/ *,char*,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/ * properties_get_or_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct wpa_dbus_object_desc*) ; 

__attribute__((used)) static DBusMessage * properties_handler(DBusMessage *message,
					struct wpa_dbus_object_desc *obj_dsc)
{
	DBusMessageIter iter;
	char *interface;
	const char *method;

	method = dbus_message_get_member(message);
	dbus_message_iter_init(message, &iter);

	if (!os_strncmp(WPA_DBUS_PROPERTIES_GET, method,
			WPAS_DBUS_METHOD_SIGNAL_PROP_MAX) ||
	    !os_strncmp(WPA_DBUS_PROPERTIES_SET, method,
			WPAS_DBUS_METHOD_SIGNAL_PROP_MAX) ||
	    !os_strncmp(WPA_DBUS_PROPERTIES_GETALL, method,
			WPAS_DBUS_METHOD_SIGNAL_PROP_MAX)) {
		/* First argument: interface name (DBUS_TYPE_STRING) */
		if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_STRING) {
			return dbus_message_new_error(message,
						      DBUS_ERROR_INVALID_ARGS,
						      NULL);
		}

		dbus_message_iter_get_basic(&iter, &interface);

		if (!os_strncmp(WPA_DBUS_PROPERTIES_GETALL, method,
				WPAS_DBUS_METHOD_SIGNAL_PROP_MAX)) {
			/* GetAll */
			return properties_get_all(message, interface, obj_dsc);
		}
		/* Get or Set */
		return properties_get_or_set(message, &iter, interface,
					     obj_dsc);
	}
	return dbus_message_new_error(message, DBUS_ERROR_UNKNOWN_METHOD,
				      NULL);
}