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
typedef  int /*<<< orphan*/  _GLFWIBUSData ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusHandlerResult ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_NOT_YET_HANDLED ; 
 int /*<<< orphan*/  IBUS_INPUT_INTERFACE ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 char* get_ibus_text_from_message (int /*<<< orphan*/ *) ; 
 int glfw_dbus_match_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_text (char const*,int) ; 

__attribute__((used)) static DBusHandlerResult
message_handler(DBusConnection *conn, DBusMessage *msg, void *user_data) {
    // To monitor signals from IBUS, use
    //  dbus-monitor --address `ibus address` "type='signal',interface='org.freedesktop.IBus.InputContext'"
    _GLFWIBUSData *ibus = (_GLFWIBUSData*)user_data;
    (void)ibus;
    const char *text;
    switch(glfw_dbus_match_signal(msg, IBUS_INPUT_INTERFACE, "CommitText", "UpdatePreeditText", "HidePreeditText", "ShowPreeditText", NULL)) {
        case 0:
            text = get_ibus_text_from_message(msg);
            debug("IBUS: CommitText: '%s'\n", text ? text : "(nil)");
            send_text(text, 2);
            break;
        case 1:
            text = get_ibus_text_from_message(msg);
            send_text(text, 1);
            debug("IBUS: UpdatePreeditText: '%s'\n", text ? text : "(nil)");
            break;
        case 2:
            debug("IBUS: HidePreeditText\n");
            break;
        case 3:
            debug("IBUS: ShowPreeditText\n");
            break;
    }
    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}