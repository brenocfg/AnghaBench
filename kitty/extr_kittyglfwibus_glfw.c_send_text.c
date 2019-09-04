#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* keyboard ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ;} ;
struct TYPE_5__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_KEY_UNKNOWN ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 TYPE_2__* _glfwFocusedWindow () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static inline void
send_text(const char *text, int state) {
    _GLFWwindow *w = _glfwFocusedWindow();
    if (w && w->callbacks.keyboard) {
        w->callbacks.keyboard((GLFWwindow*) w, GLFW_KEY_UNKNOWN, 0, GLFW_PRESS, 0, text, state);
    }
}