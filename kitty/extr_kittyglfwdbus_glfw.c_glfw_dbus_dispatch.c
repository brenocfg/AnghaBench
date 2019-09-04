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
 scalar_t__ dbus_connection_dispatch (int /*<<< orphan*/ *) ; 

void
glfw_dbus_dispatch(DBusConnection *conn) {
    while(dbus_connection_dispatch(conn) == DBUS_DISPATCH_DATA_REMAINS);
}