#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  input_ctx_path; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ _GLFWIBUSData ;
struct TYPE_12__ {int /*<<< orphan*/  ibus_keycode; int /*<<< orphan*/  ibus_sym; int /*<<< orphan*/  action; int /*<<< orphan*/  glfw_modifiers; } ;
typedef  TYPE_2__ KeyEvent ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  IBUS_INPUT_INTERFACE ; 
 int /*<<< orphan*/  IBUS_SERVICE ; 
 int /*<<< orphan*/  check_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  glfw_dbus_call_method_with_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibus_key_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_event_processed ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 

GLFWbool
ibus_process_key(const KeyEvent *ev_, _GLFWIBUSData *ibus) {
    if (!check_connection(ibus)) return GLFW_FALSE;
    KeyEvent *ev = malloc(sizeof(KeyEvent));
    if (!ev) return GLFW_FALSE;
    memcpy(ev, ev_, sizeof(KeyEvent));
    uint32_t state = ibus_key_state(ev->glfw_modifiers, ev->action);
    if (!glfw_dbus_call_method_with_reply(
            ibus->conn, IBUS_SERVICE, ibus->input_ctx_path, IBUS_INPUT_INTERFACE, "ProcessKeyEvent",
            3000, key_event_processed, ev,
            DBUS_TYPE_UINT32, &ev->ibus_sym, DBUS_TYPE_UINT32, &ev->ibus_keycode, DBUS_TYPE_UINT32,
            &state, DBUS_TYPE_INVALID)) {
        free(ev);
        return GLFW_FALSE;
    }
    return GLFW_TRUE;
}