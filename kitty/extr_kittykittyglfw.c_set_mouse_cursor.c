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
struct TYPE_3__ {scalar_t__ handle; } ;
typedef  int MouseShape ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  ARROW 129 
#define  HAND 128 
 int /*<<< orphan*/  arrow_cursor ; 
 int /*<<< orphan*/  click_cursor ; 
 int /*<<< orphan*/  glfwSetCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ global_state ; 
 int /*<<< orphan*/  standard_cursor ; 

void
set_mouse_cursor(MouseShape type) {
    if (global_state.callback_os_window) {
        GLFWwindow *w = (GLFWwindow*)global_state.callback_os_window->handle;
        switch(type) {
            case HAND:
                glfwSetCursor(w, click_cursor);
                break;
            case ARROW:
                glfwSetCursor(w, arrow_cursor);
                break;
            default:
                glfwSetCursor(w, standard_cursor);
                break;
        }
    }
}