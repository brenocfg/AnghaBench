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
struct TYPE_3__ {double last_mouse_activity_at; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 TYPE_2__ global_state ; 
 scalar_t__ is_window_ready_for_callbacks () ; 
 double monotonic () ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  scroll_event (double,double,int) ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_mouse_cursor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scroll_callback(GLFWwindow *w, double xoffset, double yoffset, int flags) {
    if (!set_callback_window(w)) return;
    show_mouse_cursor(w);
    double now = monotonic();
    global_state.callback_os_window->last_mouse_activity_at = now;
    if (is_window_ready_for_callbacks()) scroll_event(xoffset, yoffset, flags);
    request_tick_callback();
    global_state.callback_os_window = NULL;
}