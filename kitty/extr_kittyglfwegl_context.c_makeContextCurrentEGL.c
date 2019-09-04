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
struct TYPE_9__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  surface; } ;
struct TYPE_10__ {TYPE_2__ egl; } ;
struct TYPE_11__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {int /*<<< orphan*/  contextSlot; TYPE_1__ egl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 int /*<<< orphan*/  EGL_NO_SURFACE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformSetTls (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  eglGetError () ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getEGLErrorString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void makeContextCurrentEGL(_GLFWwindow* window)
{
    if (window)
    {
        if (!eglMakeCurrent(_glfw.egl.display,
                            window->context.egl.surface,
                            window->context.egl.surface,
                            window->context.egl.handle))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "EGL: Failed to make context current: %s",
                            getEGLErrorString(eglGetError()));
            return;
        }
    }
    else
    {
        if (!eglMakeCurrent(_glfw.egl.display,
                            EGL_NO_SURFACE,
                            EGL_NO_SURFACE,
                            EGL_NO_CONTEXT))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "EGL: Failed to clear current context: %s",
                            getEGLErrorString(eglGetError()));
            return;
        }
    }

    _glfwPlatformSetTls(&_glfw.contextSlot, window);
}