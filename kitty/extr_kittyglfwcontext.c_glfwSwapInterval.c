#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* swapInterval ) (int) ;} ;
struct TYPE_6__ {TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  contextSlot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int) ; 

void glfwSwapInterval(int interval)
{
    _GLFWwindow* window;

    _GLFW_REQUIRE_INIT();

    window = _glfwPlatformGetTls(&_glfw.contextSlot);
    if (!window)
    {
        _glfwInputError(GLFW_NO_CURRENT_CONTEXT,
                        "Cannot set swap interval without a current OpenGL or OpenGL ES context");
        return;
    }

    window->context.swapInterval(interval);
}