#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum Capabilities { ____Placeholder_Capabilities } Capabilities ;
struct TYPE_7__ {int /*<<< orphan*/  ok; scalar_t__ input_ctx_path; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ _GLFWIBUSData ;
struct TYPE_8__ {int /*<<< orphan*/  message_function; } ;
typedef  TYPE_2__ DBusObjectPathVTable ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int IBUS_CAP_FOCUS ; 
 int IBUS_CAP_PREEDIT_TEXT ; 
 int /*<<< orphan*/  IBUS_INPUT_INTERFACE ; 
 int /*<<< orphan*/  IBUS_SERVICE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ _glfw_strdup (char const*) ; 
 int /*<<< orphan*/  dbus_bus_add_match (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_try_register_object_path (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glfw_dbus_call_method_no_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_dbus_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_ibus_set_cursor_geometry (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_ibus_set_focused (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_handler ; 

void
input_context_created(DBusMessage *msg, const char* errmsg, void *data) {
    if (errmsg) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "IBUS: Failed to create input context with error: %s", errmsg);
        return;
    }
    const char *path = NULL;
    if (!glfw_dbus_get_args(msg, "Failed to get IBUS context path from reply", DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID)) return;
    _GLFWIBUSData *ibus = (_GLFWIBUSData*)data;
    free((void*)ibus->input_ctx_path);
    ibus->input_ctx_path = _glfw_strdup(path);
    if (!ibus->input_ctx_path) return;
    dbus_bus_add_match(ibus->conn, "type='signal',interface='org.freedesktop.IBus.InputContext'", NULL);
    DBusObjectPathVTable ibus_vtable = {.message_function = message_handler};
    dbus_connection_try_register_object_path(ibus->conn, ibus->input_ctx_path, &ibus_vtable, ibus, NULL);
    enum Capabilities caps = IBUS_CAP_FOCUS | IBUS_CAP_PREEDIT_TEXT;
    if (!glfw_dbus_call_method_no_reply(ibus->conn, IBUS_SERVICE, ibus->input_ctx_path, IBUS_INPUT_INTERFACE, "SetCapabilities", DBUS_TYPE_UINT32, &caps, DBUS_TYPE_INVALID)) return;
    ibus->ok = GLFW_TRUE;
    glfw_ibus_set_focused(ibus, GLFW_FALSE);
    glfw_ibus_set_cursor_geometry(ibus, 0, 0, 0, 0);
    debug("Connected to IBUS daemon for IME input management\n");
}