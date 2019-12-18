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
typedef  int dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_DICT_ENTRY ; 
 int FALSE ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 

dbus_bool_t wpa_dbus_dict_has_dict_entry(DBusMessageIter *iter_dict)
{
	if (!iter_dict)
		return FALSE;
	return dbus_message_iter_get_arg_type(iter_dict) ==
		DBUS_TYPE_DICT_ENTRY;
}