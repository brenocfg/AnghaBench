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
struct TYPE_3__ {int is_damaged; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 TYPE_2__ global_state ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
refresh_callback(GLFWwindow *w) {
    if (!set_callback_window(w)) return;
    global_state.callback_os_window->is_damaged = true;
    global_state.callback_os_window = NULL;
    request_tick_callback();
}