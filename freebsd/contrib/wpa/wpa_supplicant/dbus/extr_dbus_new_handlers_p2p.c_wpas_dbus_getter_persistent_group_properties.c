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
struct wpa_dbus_property_desc {int dummy; } ;
struct network_handler_args {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_getter_network_properties (struct wpa_dbus_property_desc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct network_handler_args*) ; 

dbus_bool_t wpas_dbus_getter_persistent_group_properties(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct network_handler_args *net = user_data;

	/* Leveraging the fact that persistent group object is still
	 * represented in same manner as network within.
	 */
	return wpas_dbus_getter_network_properties(property_desc, iter, error, net);
}