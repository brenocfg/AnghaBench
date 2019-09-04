#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int has_pending_closes; int /*<<< orphan*/ * callback_os_window; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 TYPE_1__ global_state ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
window_close_callback(GLFWwindow* window) {
    if (!set_callback_window(window)) return;
    global_state.has_pending_closes = true;
    request_tick_callback();
    global_state.callback_os_window = NULL;
}