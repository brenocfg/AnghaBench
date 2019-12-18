#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  hovered; } ;
struct TYPE_8__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_7__ {TYPE_3__* pointerFocus; int /*<<< orphan*/  serial; } ;
struct TYPE_9__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputCursorEnter (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleLeave(void* data,
                               struct wl_pointer* pointer,
                               uint32_t serial,
                               struct wl_surface* surface)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;

    if (!window)
        return;

    window->wl.hovered = GLFW_FALSE;

    _glfw.wl.serial = serial;
    _glfw.wl.pointerFocus = NULL;
    _glfwInputCursorEnter(window, GLFW_FALSE);
}