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
struct TYPE_4__ {scalar_t__ handle; } ;
struct TYPE_3__ {size_t num_os_windows; TYPE_2__* os_windows; TYPE_2__* callback_os_window; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 TYPE_2__* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 TYPE_1__ global_state ; 

__attribute__((used)) static inline bool
set_callback_window(GLFWwindow *w) {
    global_state.callback_os_window = glfwGetWindowUserPointer(w);
    if (global_state.callback_os_window) return true;
    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        if ((GLFWwindow*)(global_state.os_windows[i].handle) == w) {
            global_state.callback_os_window = global_state.os_windows + i;
            return true;
        }
    }
    return false;
}