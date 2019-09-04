#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int has_pending_resizes; TYPE_2__* callback_os_window; } ;
struct TYPE_4__ {int from_os_notification; int in_progress; int os_says_resize_complete; } ;
struct TYPE_5__ {TYPE_1__ live_resize; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 TYPE_3__ global_state ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
live_resize_callback(GLFWwindow *w, bool started) {
    if (!set_callback_window(w)) return;
    global_state.callback_os_window->live_resize.from_os_notification = true;
    global_state.callback_os_window->live_resize.in_progress = true;
    global_state.has_pending_resizes = true;
    if (!started) {
        global_state.callback_os_window->live_resize.os_says_resize_complete = true;
        request_tick_callback();
    }
    global_state.callback_os_window = NULL;
}