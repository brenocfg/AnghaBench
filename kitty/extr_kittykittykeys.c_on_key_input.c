#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* screen; } ;
struct TYPE_15__ {int /*<<< orphan*/  id; TYPE_1__ render_data; } ;
typedef  TYPE_3__ Window ;
struct TYPE_14__ {scalar_t__ mEXTENDED_KEYBOARD; int /*<<< orphan*/  mDECARM; } ;
struct TYPE_16__ {TYPE_2__ modes; scalar_t__ scrolled_by; } ;
struct TYPE_12__ {int /*<<< orphan*/  boss; scalar_t__ in_sequence_mode; int /*<<< orphan*/  callback_os_window; } ;
typedef  TYPE_4__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int GLFW_KEY_LEFT_ALT ; 
 int GLFW_KEY_LEFT_CONTROL ; 
 int GLFW_KEY_LEFT_SHIFT ; 
 int GLFW_KEY_RIGHT_ALT ; 
 int GLFW_KEY_RIGHT_CONTROL ; 
 int GLFW_KEY_RIGHT_SHIFT ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int GLFW_REPEAT ; 
 scalar_t__ OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  SCROLL_FULL ; 
 TYPE_3__* active_window () ; 
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 scalar_t__ check_if_special (int,int,int) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 TYPE_10__ global_state ; 
 int /*<<< orphan*/  hide_mouse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ascii_control_char (char const) ; 
 int /*<<< orphan*/  is_modifier_key (int) ; 
 int /*<<< orphan*/  mouse_hide_wait ; 
 int /*<<< orphan*/  process_sequence ; 
 int /*<<< orphan*/  schedule_write_to_child (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_draw_overlay_text (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  screen_history_scroll (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_key_to_child (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  update_ime_position (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 

void
on_key_input(int key, int scancode, int action, int mods, const char* text, int state) {
    Window *w = active_window();
    debug("on_key_input: glfw key: %d native_code: 0x%x action: %s mods: 0x%x text: '%s' state: %d ",
            key, scancode,
            (action == GLFW_RELEASE ? "RELEASE" : (action == GLFW_PRESS ? "PRESS" : "REPEAT")),
            mods, text, state);
    if (!w) { debug("no active window, ignoring\n"); return; }
    if (OPT(mouse_hide_wait) < 0 && !is_modifier_key(key)) hide_mouse(global_state.callback_os_window);
    Screen *screen = w->render_data.screen;
    switch(state) {
        case 1:  // update pre-edit text
            update_ime_position(global_state.callback_os_window, w, screen);
            screen_draw_overlay_text(screen, text);
            debug("updated pre-edit text: '%s'\n", text);
            return;
        case 2:  // commit text
            if (text && *text) {
                schedule_write_to_child(w->id, 1, text, strlen(text));
                debug("committed pre-edit text: %s\n", text);
            } else debug("committed pre-edit text: (null)\n");
            return;
        case 0:
            // for macOS, update ime position on every key input
            // because the position is required before next input
#if defined(__APPLE__)
            update_ime_position(global_state.callback_os_window, w, screen);
#endif
            break;
        default:
            debug("invalid state, ignoring\n");
            return;
    }
    if (global_state.in_sequence_mode) {
        debug("in sequence mode, handling as shortcut\n");
        if (
            action != GLFW_RELEASE &&
            key != GLFW_KEY_LEFT_SHIFT && key != GLFW_KEY_RIGHT_SHIFT && key != GLFW_KEY_LEFT_ALT && key != GLFW_KEY_RIGHT_ALT && key != GLFW_KEY_LEFT_CONTROL && key != GLFW_KEY_RIGHT_CONTROL
        ) call_boss(process_sequence, "iiii", key, scancode, action, mods);
        return;
    }
    bool has_text = text && !is_ascii_control_char(text[0]);
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (check_if_special(key, mods, scancode)) {
            PyObject *ret = PyObject_CallMethod(global_state.boss, "dispatch_special_key", "iiii", key, scancode, action, mods);
            if (ret == NULL) { PyErr_Print(); }
            else {
                bool consumed = ret == Py_True;
                Py_DECREF(ret);
                if (consumed) {
                    debug("handled as shortcut\n");
                    return;
                }
            }
        }
    }
    if (action == GLFW_REPEAT && !screen->modes.mDECARM) {
        debug("discarding repeat key event as DECARM is off\n");
        return;
    }
    if (screen->scrolled_by && action == GLFW_PRESS && !is_modifier_key(key)) {
        screen_history_scroll(screen, SCROLL_FULL, false);  // scroll back to bottom
    }
    bool ok_to_send = action == GLFW_PRESS || action == GLFW_REPEAT || screen->modes.mEXTENDED_KEYBOARD;
    if (ok_to_send) {
        if (has_text) {
            schedule_write_to_child(w->id, 1, text, strlen(text));
            debug("sent text to child\n");
        } else {
            send_key_to_child(w, key, mods, action);
            debug("sent key to child\n");
        }
    } else {
        debug("ignoring as keyboard mode does not allow %s events\n", action == GLFW_RELEASE ? "release" : "repeat");
    }
}