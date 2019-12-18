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
struct wpa_global {int dummy; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  scalar_t__ dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wpa_debug_level ; 
 int /*<<< orphan*/  wpa_debug_timestamp ; 
 int /*<<< orphan*/  wpa_supplicant_set_debug_params (struct wpa_global*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_setter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

dbus_bool_t wpas_dbus_setter_debug_show_keys(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_global *global = user_data;
	dbus_bool_t val;

	if (!wpas_dbus_simple_property_setter(iter, error, DBUS_TYPE_BOOLEAN,
					      &val))
		return FALSE;

	wpa_supplicant_set_debug_params(global, wpa_debug_level,
					wpa_debug_timestamp,
					val ? 1 : 0);
	return TRUE;
}