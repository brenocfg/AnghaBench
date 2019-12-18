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
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 char** debug_strings ; 
 int wpa_debug_level ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_debug_level(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	const char *str;
	int idx = wpa_debug_level;

	if (idx < 0)
		idx = 0;
	if (idx > 5)
		idx = 5;
	str = debug_strings[idx];
	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING,
						&str, error);
}