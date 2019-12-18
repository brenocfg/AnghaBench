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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dbus_bool_t wpa_dbus_dict_close_write(DBusMessageIter *iter,
				      DBusMessageIter *iter_dict)
{
	if (!iter || !iter_dict)
		return FALSE;

	return dbus_message_iter_close_container(iter, iter_dict);
}