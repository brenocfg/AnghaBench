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
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_BUS_SESSION ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  add_dbus_timeout ; 
 int /*<<< orphan*/  add_dbus_watch ; 
 int /*<<< orphan*/ * dbus_bus_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_timeout_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_watch_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_init (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_error_is_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dbus_timeout ; 
 int /*<<< orphan*/  remove_dbus_watch ; 
 int /*<<< orphan*/  report_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * session_bus ; 
 int /*<<< orphan*/  toggle_dbus_timeout ; 
 int /*<<< orphan*/  toggle_dbus_watch ; 

__attribute__((used)) static void
glfw_dbus_connect_to_session_bus() {
    DBusError error;
    dbus_error_init(&error);
    if (session_bus) {
        dbus_connection_unref(session_bus);
    }
    session_bus = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        report_error(&error, "Failed to connect to DBUS session bus");
        session_bus = NULL;
        return;
    }
    static const char *name = "session-bus";
    if (!dbus_connection_set_watch_functions(session_bus, add_dbus_watch, remove_dbus_watch, toggle_dbus_watch, (void*)name, NULL)) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to set DBUS watches on connection to: %s", name);
        dbus_connection_close(session_bus);
        dbus_connection_unref(session_bus);
        return;
    }
    if (!dbus_connection_set_timeout_functions(session_bus, add_dbus_timeout, remove_dbus_timeout, toggle_dbus_timeout, (void*)name, NULL)) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to set DBUS timeout functions on connection to: %s", name);
        dbus_connection_close(session_bus);
        dbus_connection_unref(session_bus);
        return;
    }

}