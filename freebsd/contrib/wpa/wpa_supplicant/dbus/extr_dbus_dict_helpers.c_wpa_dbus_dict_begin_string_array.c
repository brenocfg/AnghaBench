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
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING_AS_STRING ; 
 int /*<<< orphan*/  wpa_dbus_dict_begin_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dbus_bool_t wpa_dbus_dict_begin_string_array(DBusMessageIter *iter_dict,
					     const char *key,
					     DBusMessageIter *iter_dict_entry,
					     DBusMessageIter *iter_dict_val,
					     DBusMessageIter *iter_array)
{
	return wpa_dbus_dict_begin_array(
		iter_dict, key,
		DBUS_TYPE_STRING_AS_STRING,
		iter_dict_entry, iter_dict_val, iter_array);
}