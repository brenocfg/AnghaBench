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
struct wpa_supplicant {int dummy; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
#define  WPAS_P2P_ROLE_CLIENT 129 
#define  WPAS_P2P_ROLE_GO 128 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int wpas_get_p2p_role (struct wpa_supplicant*) ; 

dbus_bool_t wpas_dbus_getter_p2p_role(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	char *str;

	switch (wpas_get_p2p_role(wpa_s)) {
	case WPAS_P2P_ROLE_GO:
		str = "GO";
		break;
	case WPAS_P2P_ROLE_CLIENT:
		str = "client";
		break;
	default:
		str = "device";
		break;
	}

	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING, &str,
						error);
}