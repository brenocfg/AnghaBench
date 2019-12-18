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
struct wpas_dbus_priv {int /*<<< orphan*/ * con; } ;
struct wpa_dbus_object_desc {int /*<<< orphan*/  path; int /*<<< orphan*/ * connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  message; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ DBusObjectPathVTable ;
typedef  TYPE_2__ DBusError ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_OBJECT_PATH_IN_USE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  dbus_connection_try_register_object_path (int /*<<< orphan*/ *,char const*,TYPE_1__*,struct wpa_dbus_object_desc*,TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_2__*) ; 
 int /*<<< orphan*/  free_dbus_object_desc_cb ; 
 int /*<<< orphan*/  message_handler ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

int wpa_dbus_register_object_per_iface(struct wpas_dbus_priv *ctrl_iface,
				       const char *path, const char *ifname,
				       struct wpa_dbus_object_desc *obj_desc)
{
	DBusConnection *con;
	DBusError error;
	DBusObjectPathVTable vtable = {
		&free_dbus_object_desc_cb, &message_handler,
		NULL, NULL, NULL, NULL
	};

	/* Do nothing if the control interface is not turned on */
	if (ctrl_iface == NULL)
		return 0;

	con = ctrl_iface->con;
	obj_desc->connection = con;
	obj_desc->path = os_strdup(path);

	dbus_error_init(&error);
	/* Register the message handler for the interface functions */
	if (!dbus_connection_try_register_object_path(con, path, &vtable,
						      obj_desc, &error)) {
		if (os_strcmp(error.name, DBUS_ERROR_OBJECT_PATH_IN_USE) == 0) {
			wpa_printf(MSG_DEBUG, "dbus: %s", error.message);
		} else {
			wpa_printf(MSG_ERROR,
				   "dbus: Could not set up message handler for interface %s object %s (error: %s message: %s)",
				   ifname, path, error.name, error.message);
		}
		dbus_error_free(&error);
		return -1;
	}

	dbus_error_free(&error);
	return 0;
}