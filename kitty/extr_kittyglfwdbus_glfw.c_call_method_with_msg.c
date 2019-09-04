#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dbus_pending_callback ;
struct TYPE_4__ {void* user_data; scalar_t__ callback; } ;
typedef  TYPE_1__ MethodResponse ;
typedef  int /*<<< orphan*/  GLFWbool ;
typedef  int /*<<< orphan*/  DBusPendingCall ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dbus_connection_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_connection_send_with_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  dbus_message_get_destination (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_get_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_pending_call_set_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  method_reply_received ; 

GLFWbool
call_method_with_msg(DBusConnection *conn, DBusMessage *msg, int timeout, dbus_pending_callback callback, void *user_data) {
    GLFWbool retval = GLFW_FALSE;
#define REPORT(errs) _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to call DBUS method: node=%s path=%s interface=%s method=%s, with error: %s", dbus_message_get_destination(msg), dbus_message_get_path(msg), dbus_message_get_interface(msg), dbus_message_get_member(msg), errs)
    if (callback) {
        DBusPendingCall *pending = NULL;
        if (dbus_connection_send_with_reply(conn, msg, &pending, timeout)) {
            MethodResponse *res = malloc(sizeof(MethodResponse));
            if (!res) return GLFW_FALSE;
            res->callback = callback;
            res->user_data = user_data;
            dbus_pending_call_set_notify(pending, method_reply_received, res, free);
            retval = GLFW_TRUE;
        } else {
            REPORT("out of memory");
        }
    } else {
        if (dbus_connection_send(conn, msg, NULL)) {
            retval = GLFW_TRUE;
        } else {
            REPORT("out of memory");
        }
    }
    return retval;
#undef REPORT
}