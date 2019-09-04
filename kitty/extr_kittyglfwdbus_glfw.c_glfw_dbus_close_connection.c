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
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 

void
glfw_dbus_close_connection(DBusConnection *conn) {
    dbus_connection_close(conn);
    dbus_connection_unref(conn);
}