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
 scalar_t__ DBUS_DISPATCH_DATA_REMAINS ; 
 int /*<<< orphan*/  dbus_connection_dispatch (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_connection_get_dispatch_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch_data(DBusConnection *con)
{
	while (dbus_connection_get_dispatch_status(con) ==
	       DBUS_DISPATCH_DATA_REMAINS)
		dbus_connection_dispatch(con);
}