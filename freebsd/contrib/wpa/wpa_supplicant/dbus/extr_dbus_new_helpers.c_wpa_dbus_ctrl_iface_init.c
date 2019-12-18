#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;
struct wpa_dbus_object_desc {int /*<<< orphan*/  path; int /*<<< orphan*/  connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  message; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ DBusObjectPathVTable ;
typedef  TYPE_2__ DBusError ;

/* Variables and functions */
#define  DBUS_REQUEST_NAME_REPLY_ALREADY_OWNER 131 
#define  DBUS_REQUEST_NAME_REPLY_EXISTS 130 
#define  DBUS_REQUEST_NAME_REPLY_IN_QUEUE 129 
#define  DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int dbus_bus_request_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_connection_register_object_path (int /*<<< orphan*/ ,char*,TYPE_1__*,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_2__*) ; 
 int /*<<< orphan*/  free_dbus_object_desc_cb ; 
 int /*<<< orphan*/  message_handler ; 
 int /*<<< orphan*/  os_strdup (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wpa_dbus_ctrl_iface_init(struct wpas_dbus_priv *iface,
			     char *dbus_path, char *dbus_service,
			     struct wpa_dbus_object_desc *obj_desc)
{
	DBusError error;
	int ret = -1;
	DBusObjectPathVTable wpa_vtable = {
		&free_dbus_object_desc_cb, &message_handler,
		NULL, NULL, NULL, NULL
	};

	obj_desc->connection = iface->con;
	obj_desc->path = os_strdup(dbus_path);

	/* Register the message handler for the global dbus interface */
	if (!dbus_connection_register_object_path(iface->con, dbus_path,
						  &wpa_vtable, obj_desc)) {
		wpa_printf(MSG_ERROR, "dbus: Could not set up message handler");
		return -1;
	}

	/* Register our service with the message bus */
	dbus_error_init(&error);
	switch (dbus_bus_request_name(iface->con, dbus_service, 0, &error)) {
	case DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER:
		ret = 0;
		break;
	case DBUS_REQUEST_NAME_REPLY_EXISTS:
	case DBUS_REQUEST_NAME_REPLY_IN_QUEUE:
	case DBUS_REQUEST_NAME_REPLY_ALREADY_OWNER:
		wpa_printf(MSG_ERROR,
			   "dbus: Could not request service name: already registered");
		break;
	default:
		wpa_printf(MSG_ERROR,
			   "dbus: Could not request service name: %s %s",
			   error.name, error.message);
		break;
	}
	dbus_error_free(&error);

	if (ret != 0)
		return -1;

	wpa_printf(MSG_DEBUG, "Providing DBus service '%s'.", dbus_service);

	return 0;
}