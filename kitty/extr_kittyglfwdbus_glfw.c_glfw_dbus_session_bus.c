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
 int /*<<< orphan*/  glfw_dbus_connect_to_session_bus () ; 
 int /*<<< orphan*/ * session_bus ; 

DBusConnection *
glfw_dbus_session_bus() {
    if (!session_bus) glfw_dbus_connect_to_session_bus();
    return session_bus;
}