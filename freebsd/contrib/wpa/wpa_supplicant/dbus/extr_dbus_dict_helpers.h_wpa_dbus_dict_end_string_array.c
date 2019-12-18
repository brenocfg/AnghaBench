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
 int /*<<< orphan*/  wpa_dbus_dict_end_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline dbus_bool_t
wpa_dbus_dict_end_string_array(DBusMessageIter *iter_dict,
			       DBusMessageIter *iter_dict_entry,
			       DBusMessageIter *iter_dict_val,
			       DBusMessageIter *iter_array)
{
	return wpa_dbus_dict_end_array(iter_dict, iter_dict_entry,
				       iter_dict_val, iter_array);
}