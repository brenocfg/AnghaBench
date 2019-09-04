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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ action; int /*<<< orphan*/  keycode; } ;
typedef  TYPE_1__ KeyEvent ;
typedef  int GLFWbool ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_RELEASE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  glfw_dbus_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_xkb_key_from_ime (TYPE_1__*,int,int) ; 

void
key_event_processed(DBusMessage *msg, const char* errmsg, void *data) {
    uint32_t handled = 0;
    KeyEvent *ev = (KeyEvent*)data;
    GLFWbool is_release = ev->action == GLFW_RELEASE;
    GLFWbool failed = GLFW_FALSE;
    if (errmsg) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "IBUS: Failed to process key with error: %s", errmsg);
        failed = GLFW_TRUE;
    } else {
        glfw_dbus_get_args(msg, "Failed to get IBUS handled key from reply", DBUS_TYPE_BOOLEAN, &handled, DBUS_TYPE_INVALID);
        debug("IBUS processed scancode: 0x%x release: %d handled: %u\n", ev->keycode, is_release, handled);
    }
    glfw_xkb_key_from_ime(ev, handled ? GLFW_TRUE : GLFW_FALSE, failed);
    free(ev);
}