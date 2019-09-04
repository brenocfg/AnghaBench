#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  surface; } ;
struct TYPE_10__ {TYPE_2__ egl; } ;
struct TYPE_11__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {TYPE_1__ egl; int /*<<< orphan*/  contextSlot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swapBuffersEGL(_GLFWwindow* window)
{
    if (window != _glfwPlatformGetTls(&_glfw.contextSlot))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "EGL: The context must be current on the calling thread when swapping buffers");
        return;
    }

    eglSwapBuffers(_glfw.egl.display, window->context.egl.surface);
}