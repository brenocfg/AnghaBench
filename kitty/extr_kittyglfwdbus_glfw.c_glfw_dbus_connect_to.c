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
typedef  scalar_t__ GLFWbool ;
typedef  int /*<<< orphan*/  DBusError ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  add_dbus_timeout ; 
 int /*<<< orphan*/  add_dbus_watch ; 
 int /*<<< orphan*/  dbus_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_connection_open_private (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_exit_on_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_set_timeout_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_watch_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dbus_timeout ; 
 int /*<<< orphan*/  remove_dbus_watch ; 
 int /*<<< orphan*/  report_error (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  toggle_dbus_timeout ; 
 int /*<<< orphan*/  toggle_dbus_watch ; 

DBusConnection*
glfw_dbus_connect_to(const char *path, const char* err_msg, const char *name, GLFWbool register_on_bus) {
    DBusError err;
    dbus_error_init(&err);
    DBusConnection *ans = dbus_connection_open_private(path, &err);
    if (!ans) {
        report_error(&err, err_msg);
        return NULL;
    }
    dbus_connection_set_exit_on_disconnect(ans, FALSE);
    dbus_error_free(&err);
    if (register_on_bus) {
        if (!dbus_bus_register(ans, &err)) {
            report_error(&err, err_msg);
            return NULL;
        }
    }
    if (!dbus_connection_set_watch_functions(ans, add_dbus_watch, remove_dbus_watch, toggle_dbus_watch, (void*)name, NULL)) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to set DBUS watches on connection to: %s", path);
        dbus_connection_close(ans);
        dbus_connection_unref(ans);
        return NULL;
    }
    if (!dbus_connection_set_timeout_functions(ans, add_dbus_timeout, remove_dbus_timeout, toggle_dbus_timeout, (void*)name, NULL)) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to set DBUS timeout functions on connection to: %s", path);
        dbus_connection_close(ans);
        dbus_connection_unref(ans);
        return NULL;
    }
    return ans;
}