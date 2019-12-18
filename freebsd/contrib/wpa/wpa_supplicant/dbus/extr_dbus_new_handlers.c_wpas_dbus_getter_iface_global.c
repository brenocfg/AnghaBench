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
struct wpa_dbus_property_desc {int /*<<< orphan*/  data; int /*<<< orphan*/  dbus_property; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dbus_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int wpa_config_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_iface_global(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	int ret;
	char buf[250];
	char *p = buf;

	if (!property_desc->data) {
		dbus_set_error(error, DBUS_ERROR_INVALID_ARGS,
			       "Unhandled interface property %s",
			       property_desc->dbus_property);
		return FALSE;
	}

	ret = wpa_config_get_value(property_desc->data, wpa_s->conf, buf,
				   sizeof(buf));
	if (ret < 0)
		*p = '\0';

	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING, &p,
						error);
}