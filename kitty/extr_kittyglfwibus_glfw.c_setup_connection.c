#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * conn; int /*<<< orphan*/ * input_ctx_path; int /*<<< orphan*/  address; scalar_t__ address_file_name; int /*<<< orphan*/  ok; } ;
typedef  TYPE_1__ _GLFWIBUSData ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TIMEOUT_USE_DEFAULT ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  IBUS_INTERFACE ; 
 int /*<<< orphan*/  IBUS_PATH ; 
 int /*<<< orphan*/  IBUS_SERVICE ; 
 scalar_t__ _glfw_strdup (char const*) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 char* get_ibus_address_file_name () ; 
 int /*<<< orphan*/  glfw_dbus_call_method_with_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_dbus_close_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glfw_dbus_connect_to (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_context_created ; 
 int /*<<< orphan*/  read_ibus_address (TYPE_1__*) ; 

GLFWbool
setup_connection(_GLFWIBUSData *ibus) {
    const char *client_name = "GLFW_Application";
    const char *address_file_name = get_ibus_address_file_name();
    ibus->ok = GLFW_FALSE;
    if (!address_file_name) return GLFW_FALSE;
    free((void*)ibus->address_file_name);
    ibus->address_file_name = _glfw_strdup(address_file_name);
    if (!read_ibus_address(ibus)) return GLFW_FALSE;
    if (ibus->conn) {
        glfw_dbus_close_connection(ibus->conn);
        ibus->conn = NULL;
    }
    debug("Connecting to IBUS daemon @ %s for IME input management\n", ibus->address);
    ibus->conn = glfw_dbus_connect_to(ibus->address, "Failed to connect to the IBUS daemon, with error", "ibus", GLFW_FALSE);
    if (!ibus->conn) return GLFW_FALSE;
    free((void*)ibus->input_ctx_path); ibus->input_ctx_path = NULL;
    if (!glfw_dbus_call_method_with_reply(
            ibus->conn, IBUS_SERVICE, IBUS_PATH, IBUS_INTERFACE, "CreateInputContext", DBUS_TIMEOUT_USE_DEFAULT, input_context_created, ibus,
            DBUS_TYPE_STRING, &client_name, DBUS_TYPE_INVALID)) {
        return GLFW_FALSE;
    }
    return GLFW_TRUE;
}