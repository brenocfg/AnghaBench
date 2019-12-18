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
struct wpa_dbus_property_desc {int /*<<< orphan*/  dbus_interface; scalar_t__ dbus_property; } ;
struct wpa_dbus_object_desc {int /*<<< orphan*/ * prop_changed_flags; struct wpa_dbus_property_desc* properties; } ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_get_object_path_data (int /*<<< orphan*/ *,char const*,void**) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  flush_object_timeout_handler ; 
 int /*<<< orphan*/  send_prop_changed_signal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct wpa_dbus_object_desc*) ; 

void wpa_dbus_flush_object_changed_properties(DBusConnection *con,
					      const char *path)
{
	struct wpa_dbus_object_desc *obj_desc = NULL;
	const struct wpa_dbus_property_desc *dsc;
	int i;

	dbus_connection_get_object_path_data(con, path, (void **) &obj_desc);
	if (!obj_desc)
		return;
	eloop_cancel_timeout(flush_object_timeout_handler, con, obj_desc);

	for (dsc = obj_desc->properties, i = 0; dsc && dsc->dbus_property;
	     dsc++, i++) {
		if (obj_desc->prop_changed_flags == NULL ||
		    !obj_desc->prop_changed_flags[i])
			continue;
		send_prop_changed_signal(con, path, dsc->dbus_interface,
					 obj_desc);
	}
}