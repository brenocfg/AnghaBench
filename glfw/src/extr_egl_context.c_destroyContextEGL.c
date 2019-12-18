#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ handle; scalar_t__ surface; int /*<<< orphan*/ * client; } ;
struct TYPE_9__ {scalar_t__ client; TYPE_2__ egl; } ;
struct TYPE_10__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
struct TYPE_11__ {TYPE_1__ egl; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_CONTEXT ; 
 scalar_t__ EGL_NO_SURFACE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfw_dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglDestroyContext (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eglDestroySurface (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void destroyContextEGL(_GLFWwindow* window)
{
#if defined(_GLFW_X11)
    // NOTE: Do not unload libGL.so.1 while the X11 display is still open,
    //       as it will make XCloseDisplay segfault
    if (window->context.client != GLFW_OPENGL_API)
#endif // _GLFW_X11
    {
        if (window->context.egl.client)
        {
            _glfw_dlclose(window->context.egl.client);
            window->context.egl.client = NULL;
        }
    }

    if (window->context.egl.surface)
    {
        eglDestroySurface(_glfw.egl.display, window->context.egl.surface);
        window->context.egl.surface = EGL_NO_SURFACE;
    }

    if (window->context.egl.handle)
    {
        eglDestroyContext(_glfw.egl.display, window->context.egl.handle);
        window->context.egl.handle = EGL_NO_CONTEXT;
    }
}