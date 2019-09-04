#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/  ibus; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfw_ibus_set_cursor_geometry (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  glfw_ibus_set_focused (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
glfw_xkb_update_ime_state(_GLFWwindow *w, _GLFWXKBData *xkb, int which, int a, int b, int c, int d) {
    int x = 0, y = 0;
    switch(which) {
        case 1:
            glfw_ibus_set_focused(&xkb->ibus, a ? GLFW_TRUE : GLFW_FALSE);
            break;
        case 2:
            _glfwPlatformGetWindowPos(w, &x, &y);
            x += a; y += b;
            glfw_ibus_set_cursor_geometry(&xkb->ibus, x, y, c, d);
            break;
    }
}