#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* callback_os_window; scalar_t__ active_drag_in_window; } ;
struct TYPE_3__ {int is_focused; double last_mouse_activity_at; double cursor_blink_zero_time; int /*<<< orphan*/  handle; scalar_t__ last_focused_counter; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 
 int /*<<< orphan*/  WINDOW_CALLBACK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ focus_counter ; 
 int /*<<< orphan*/  focus_in_event () ; 
 int /*<<< orphan*/  glfwUpdateIMEState (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ global_state ; 
 scalar_t__ is_window_ready_for_callbacks () ; 
 double monotonic () ; 
 int /*<<< orphan*/  on_focus ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_mouse_cursor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
window_focus_callback(GLFWwindow *w, int focused) {
    global_state.active_drag_in_window = 0;
    if (!set_callback_window(w)) return;
    global_state.callback_os_window->is_focused = focused ? true : false;
    if (focused) {
        show_mouse_cursor(w);
        focus_in_event();
        global_state.callback_os_window->last_focused_counter = ++focus_counter;
    }
    double now = monotonic();
    global_state.callback_os_window->last_mouse_activity_at = now;
    global_state.callback_os_window->cursor_blink_zero_time = now;
    if (is_window_ready_for_callbacks()) {
        WINDOW_CALLBACK(on_focus, "O", focused ? Py_True : Py_False);
        glfwUpdateIMEState(global_state.callback_os_window->handle, 1, focused, 0, 0, 0);
    }
    request_tick_callback();
    global_state.callback_os_window = NULL;
}