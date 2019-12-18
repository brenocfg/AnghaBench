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
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  WPAS_DBUS_NEW_PATH ; 
 int /*<<< orphan*/  recursive_flush_changed_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wpa_dbus_flush_all_changed_properties(DBusConnection *con)
{
	recursive_flush_changed_properties(con, WPAS_DBUS_NEW_PATH);
}