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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusHandlerResult ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_HANDLED ; 
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_NOT_YET_HANDLED ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  NOTIFICATIONS_IFACE ; 
 int /*<<< orphan*/  activated_handler (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dbus_message_is_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ glfw_dbus_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DBusHandlerResult
message_handler(DBusConnection *conn, DBusMessage *msg, void *user_data) {
    (void)(user_data);
    /* printf("session_bus message_handler invoked interface: %s member: %s\n", dbus_message_get_interface(msg), dbus_message_get_member(msg)); */
    if (dbus_message_is_signal(msg, NOTIFICATIONS_IFACE, "ActionInvoked")) {
        uint32_t notification_id;
        const char *action;
        if (glfw_dbus_get_args(msg, "Failed to get args from ActionInvoked notification signal",
                    DBUS_TYPE_UINT32, &notification_id, DBUS_TYPE_STRING, &action, DBUS_TYPE_INVALID)) {
            if (activated_handler) {
                activated_handler(notification_id, action);
                return DBUS_HANDLER_RESULT_HANDLED;
            }
        }

    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}