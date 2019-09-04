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
struct TYPE_4__ {TYPE_1__* callback_os_window; } ;
struct TYPE_3__ {int* is_key_pressed; int /*<<< orphan*/  cursor_blink_zero_time; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_KEY_LAST ; 
 int GLFW_RELEASE ; 
 TYPE_2__ global_state ; 
 scalar_t__ is_window_ready_for_callbacks () ; 
 int /*<<< orphan*/  monotonic () ; 
 int /*<<< orphan*/  on_key_input (int,int,int,int,char const*,int) ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
key_callback(GLFWwindow *w, int key, int scancode, int action, int mods, const char* text, int state) {
    if (!set_callback_window(w)) return;
    global_state.callback_os_window->cursor_blink_zero_time = monotonic();
    if (key >= 0 && key <= GLFW_KEY_LAST) {
        global_state.callback_os_window->is_key_pressed[key] = action == GLFW_RELEASE ? false : true;
    }
    if (is_window_ready_for_callbacks()) on_key_input(key, scancode, action, mods, text, state);
    global_state.callback_os_window = NULL;
    request_tick_callback();
}