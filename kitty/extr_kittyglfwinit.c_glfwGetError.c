#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int code; char* description; } ;
typedef  TYPE_1__ _GLFWerror ;
struct TYPE_6__ {int /*<<< orphan*/  errorSlot; scalar_t__ initialized; } ;

/* Variables and functions */
 void* GLFW_NO_ERROR ; 
 TYPE_4__ _glfw ; 
 TYPE_1__ _glfwMainThreadError ; 
 TYPE_1__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 

int glfwGetError(const char** description)
{
    _GLFWerror* error;
    int code = GLFW_NO_ERROR;

    if (description)
        *description = NULL;

    if (_glfw.initialized)
        error = _glfwPlatformGetTls(&_glfw.errorSlot);
    else
        error = &_glfwMainThreadError;

    if (error)
    {
        code = error->code;
        error->code = GLFW_NO_ERROR;
        if (description && code)
            *description = error->description;
    }

    return code;
}