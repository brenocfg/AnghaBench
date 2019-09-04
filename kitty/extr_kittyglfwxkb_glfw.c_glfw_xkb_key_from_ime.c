#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xkb_keycode_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* keyboard ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_8__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_9__ {scalar_t__ keycode; int /*<<< orphan*/  text; int /*<<< orphan*/  glfw_modifiers; int /*<<< orphan*/  action; int /*<<< orphan*/  keysym; int /*<<< orphan*/  glfw_keycode; int /*<<< orphan*/  window_id; } ;
typedef  TYPE_3__ KeyEvent ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_KEY_UNKNOWN ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 int /*<<< orphan*/  _glfwGetKeyName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputKeyboard (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* _glfwWindowForId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  format_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfw_xkb_keysym_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
glfw_xkb_key_from_ime(KeyEvent *ev, GLFWbool handled_by_ime, GLFWbool failed) {
    _GLFWwindow *window = _glfwWindowForId(ev->window_id);
    if (failed && window && window->callbacks.keyboard) {
        // notify application to remove any existing pre-edit text
        window->callbacks.keyboard((GLFWwindow*) window, GLFW_KEY_UNKNOWN, 0, GLFW_PRESS, 0, "", 1);
    }
    static xkb_keycode_t last_handled_press_keycode = 0;
    // We filter out release events that correspond to the last press event
    // handled by the IME system. This wont fix the case of multiple key
    // presses before a release, but is better than nothing. For that case
    // you'd need to implement a ring buffer to store pending key presses.
    xkb_keycode_t prev_handled_press = last_handled_press_keycode;
    last_handled_press_keycode = 0;
    GLFWbool is_release = ev->action == GLFW_RELEASE;
    debug("From IBUS: scancode: 0x%x name: %s is_release: %d\n", ev->keycode, glfw_xkb_keysym_name(ev->keysym), is_release);
    if (window && !handled_by_ime && !(is_release && ev->keycode == prev_handled_press)) {
        debug("↳ to application: glfw_keycode: 0x%x (%s) keysym: 0x%x (%s) action: %s %s text: %s\n",
            ev->glfw_keycode, _glfwGetKeyName(ev->glfw_keycode), ev->keysym, glfw_xkb_keysym_name(ev->keysym),
            (ev->action == GLFW_RELEASE ? "RELEASE" : (ev->action == GLFW_PRESS ? "PRESS" : "REPEAT")),
            format_mods(ev->glfw_modifiers), ev->text
        );
        _glfwInputKeyboard(window, ev->glfw_keycode, ev->keysym, ev->action, ev->glfw_modifiers, ev->text, 0);
    } else debug("↳ discarded\n");
    if (!is_release && handled_by_ime) last_handled_press_keycode = ev->keycode;
}