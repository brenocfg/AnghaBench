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
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;
struct wpa_dbus_property_desc {scalar_t__ dbus_property; scalar_t__ dbus_interface; } ;
struct wpa_dbus_object_desc {int* prop_changed_flags; struct wpa_dbus_property_desc* properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPA_DBUS_SEND_PROP_CHANGED_TIMEOUT ; 
 int /*<<< orphan*/  dbus_connection_get_object_path_data (int /*<<< orphan*/ ,char const*,void**) ; 
 int /*<<< orphan*/  eloop_is_timeout_registered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_dbus_object_desc*) ; 
 int /*<<< orphan*/  flush_object_timeout_handler ; 
 scalar_t__ os_strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

void wpa_dbus_mark_property_changed(struct wpas_dbus_priv *iface,
				    const char *path, const char *interface,
				    const char *property)
{
	struct wpa_dbus_object_desc *obj_desc = NULL;
	const struct wpa_dbus_property_desc *dsc;
	int i = 0;

	if (iface == NULL)
		return;

	dbus_connection_get_object_path_data(iface->con, path,
					     (void **) &obj_desc);
	if (!obj_desc) {
		wpa_printf(MSG_ERROR,
			   "dbus: wpa_dbus_property_changed: could not obtain object's private data: %s",
			   path);
		return;
	}

	for (dsc = obj_desc->properties; dsc && dsc->dbus_property; dsc++, i++)
		if (os_strcmp(property, dsc->dbus_property) == 0 &&
		    os_strcmp(interface, dsc->dbus_interface) == 0) {
			if (obj_desc->prop_changed_flags)
				obj_desc->prop_changed_flags[i] = 1;
			break;
		}

	if (!dsc || !dsc->dbus_property) {
		wpa_printf(MSG_ERROR,
			   "dbus: wpa_dbus_property_changed: no property %s in object %s",
			   property, path);
		return;
	}

	if (!eloop_is_timeout_registered(flush_object_timeout_handler,
					 iface->con, obj_desc)) {
		eloop_register_timeout(0, WPA_DBUS_SEND_PROP_CHANGED_TIMEOUT,
				       flush_object_timeout_handler,
				       iface->con, obj_desc);
	}
}