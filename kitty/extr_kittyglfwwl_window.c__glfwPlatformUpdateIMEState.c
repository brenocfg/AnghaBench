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
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/  xkb; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  glfw_xkb_update_ime_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 

void
_glfwPlatformUpdateIMEState(_GLFWwindow *w, int which, int a, int b, int c, int d) {
    glfw_xkb_update_ime_state(w, &_glfw.wl.xkb, which, a, b, c, d);
}