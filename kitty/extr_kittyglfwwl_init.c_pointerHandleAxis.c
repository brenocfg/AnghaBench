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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  scalar_t__ uint32_t ;
struct wl_pointer {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/ * pointerFocus; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ WL_POINTER_AXIS_HORIZONTAL_SCROLL ; 
 scalar_t__ WL_POINTER_AXIS_VERTICAL_SCROLL ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputScroll (int /*<<< orphan*/ *,double,double,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int wl_fixed_to_double (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleAxis(void* data,
                              struct wl_pointer* pointer,
                              uint32_t time,
                              uint32_t axis,
                              wl_fixed_t value)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;
    double x = 0.0, y = 0.0;
    if (!window)
        return;

    assert(axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL ||
           axis == WL_POINTER_AXIS_VERTICAL_SCROLL);

    if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL)
        x = wl_fixed_to_double(value) * -1;
    else if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL)
        y = wl_fixed_to_double(value) * -1;

    _glfwInputScroll(window, x, y, 1);
}