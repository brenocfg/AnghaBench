#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {scalar_t__ client; TYPE_1__ egl; } ;
struct TYPE_6__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  EGLContext ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_NO_CONTEXT ; 
 scalar_t__ GLFW_NO_API ; 
 int /*<<< orphan*/  GLFW_NO_WINDOW_CONTEXT ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

EGLContext glfwGetEGLContext(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    _GLFW_REQUIRE_INIT_OR_RETURN(EGL_NO_CONTEXT);

    if (window->context.client == GLFW_NO_API)
    {
        _glfwInputError(GLFW_NO_WINDOW_CONTEXT, NULL);
        return EGL_NO_CONTEXT;
    }

    return window->context.egl.handle;
}