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
struct wpa_ssid {int dummy; } ;
struct wpa_dbus_property_desc {int dummy; } ;
struct network_handler_args {int /*<<< orphan*/  wpa_s; struct wpa_ssid* ssid; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_network_properties (int /*<<< orphan*/ ,struct wpa_ssid*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_setter_network_properties(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct network_handler_args *net = user_data;
	struct wpa_ssid *ssid = net->ssid;
	DBusMessageIter	variant_iter;

	dbus_message_iter_recurse(iter, &variant_iter);
	return set_network_properties(net->wpa_s, ssid, &variant_iter, error);
}