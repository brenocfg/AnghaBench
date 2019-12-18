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
struct TYPE_3__ {int /*<<< orphan*/ * handle; scalar_t__ display; } ;
struct TYPE_4__ {TYPE_1__ egl; } ;

/* Variables and functions */
 scalar_t__ EGL_NO_DISPLAY ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfw_dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eglTerminate (scalar_t__) ; 

void _glfwTerminateEGL(void)
{
    if (_glfw.egl.display)
    {
        eglTerminate(_glfw.egl.display);
        _glfw.egl.display = EGL_NO_DISPLAY;
    }

    if (_glfw.egl.handle)
    {
        _glfw_dlclose(_glfw.egl.handle);
        _glfw.egl.handle = NULL;
    }
}